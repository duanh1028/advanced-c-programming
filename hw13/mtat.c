#include<assert.h>
#include<pthread.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "bmp.h"

const char* IMAGENULLERROR = "The image is null!";
const char* THREADCREATEERROR = "Cannot create thread!";
const char* THREADSNUMERROR = "There are too many threads!";
const int BLACK = 0x00;
const int WHITE = 0xff;
const int BYTESPERPIXEL = 3;

int _get_pixel_rgb(const BMPImage* image, int index);
int _add_pixel(const BMPImage* image, int a, int i);
BMPImage* _image_copy(const BMPImage* image);
void _free_image(BMPImage* image);

typedef struct image_struct {
	BMPImage* image_original;
	BMPImage* image;
	int row;
	int num;
	int radius;
	size_t row_end;
	size_t num_end;
	bool end;
} image_struct;

void _free_image(BMPImage* image) {
	if(image != NULL) {
		free(image -> data);
	}
	free(image);
}

void* worker(void* args) {
	image_struct* args_copy = args;
	BMPImage* image_original = args_copy -> image_original;
	BMPImage* image = args_copy -> image;
	int row = args_copy -> row;
	int num = args_copy -> num;
	int radius = args_copy -> radius;
	size_t row_end = args_copy -> row_end;
	size_t num_end = args_copy -> num_end;
	
	size_t row_size = image_original -> header.image_size_bytes / image_original -> header.height_px;
	for(int a = row; a < image_original -> header.height_px; a++) {
		for(int i = num; i < image_original -> header.width_px; i++) {
			if(i == num_end && a == row_end && args_copy -> end) {
				return NULL;
			}
			int neighbor_size = 0;
			int right_num = 0;
			int upper_num = 0;
			int lower_num = 0;
			int left_num  = 0;
			int neighbor_num = 0;
			int pixel_size = _get_pixel_rgb(image_original, i * BYTESPERPIXEL + a * row_size);

			if(i - radius < 0) {                                                      // add left pixels
				for(int j = 0; j < i; j++) {
					neighbor_size += _add_pixel(image_original, j, a);
					left_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i - j - 1, a);
					left_num++;
				}
			}

			if(i + radius > image_original -> header.width_px - 1) {                  // add right pixels
				for(int j = 0; j < image_original -> header.width_px - i - 1; j++) {
					neighbor_size += _add_pixel(image_original, i + j + 1, a);
					right_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i + j + 1, a);
					right_num++;
				}
			}

			if(a - radius < 0) {                                                      //add lower pixels
				for(int j = 0; j < a; j++) {
					neighbor_size += _add_pixel(image_original, i, j);
					lower_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i, a - j - 1);
					lower_num++;
				}
			}

			if(a + radius > image_original -> header.height_px - 1) {                 //add upper pixels
				for(int j = 0; j < image_original -> header.height_px - a - 1; j++) {
					neighbor_size += _add_pixel(image_original, i, a + j + 1);
					upper_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i, a + j + 1);
					upper_num++;
				}
			}

			for(int y = 0; y < upper_num; y++) {                                      //add upper left and right pixels
				for(int x = 0; x < left_num; x++) {
					neighbor_size += _add_pixel(image_original, i - x - 1, a + y + 1);
				}
				for(int x = 0; x < right_num; x++) {
					neighbor_size += _add_pixel(image_original, i + x + 1, a + y + 1);
				}
			}

			for(int y = 0; y < lower_num; y++) {                                      //add lower left and right pixels
				for(int x = 0; x < left_num; x++) {
					neighbor_size += _add_pixel(image_original, i - x - 1, a - y - 1);
				}
				for(int x = 0; x < right_num; x++) {
					neighbor_size += _add_pixel(image_original, i + x + 1, a - y - 1);
				}
			}
			neighbor_num = lower_num + upper_num + left_num + right_num
				+ upper_num * (left_num + right_num)
				+ lower_num * (left_num + right_num);

			if(pixel_size * neighbor_num <= neighbor_size) {
				image -> data[a * row_size + i * BYTESPERPIXEL] = BLACK;	
				image -> data[a * row_size + i * BYTESPERPIXEL + 1] = BLACK;	
				image -> data[a * row_size + i * BYTESPERPIXEL + 2] = BLACK;	
			} else {
				image -> data[a * row_size + i * BYTESPERPIXEL] = WHITE;	
				image -> data[a * row_size + i * BYTESPERPIXEL + 1] = WHITE;	
				image -> data[a * row_size + i * BYTESPERPIXEL + 2] = WHITE;		
			}
		}
	}
	return NULL;
}

BMPImage* binarize(const BMPImage* image, int radius, int num_threads, const char** a_error) {
	if(image == NULL) {
		*a_error = IMAGENULLERROR;
		return NULL;
	}
	if(num_threads > image -> header.height_px * image -> header.width_px) {
		*a_error = THREADSNUMERROR;
		return NULL;
	}
	size_t pixel_per_thread = image -> header.height_px * image -> header.width_px / num_threads;
	pthread_t* threads = malloc(num_threads * sizeof(*threads));
	bool check = false;
	BMPImage* result = _image_copy(image);
	image_struct* args = malloc(sizeof(*args) * num_threads);

	for(int i = 0; i < num_threads; i++) {
		if(i == num_threads - 1) {
			check = true;
		}
		args[i] = (image_struct){
			.image_original = (BMPImage*)image,
			.image = result,
			.row = i * pixel_per_thread / image -> header.width_px,
			.num = i * pixel_per_thread % image -> header.width_px,
			.radius = radius,
			.row_end = (i + 1) * pixel_per_thread / image -> header.width_px - 1,
			.num_end = (i + 1) * pixel_per_thread % image -> header.width_px,
			.end = check,
		};
		if(args -> num_end == 0) {
			args -> num_end = image -> header.width_px;
		}
		if(pthread_create(&threads[i], NULL, worker, &args[i]) != 0) {
			*a_error = THREADCREATEERROR;
			free(args);
			free(threads);
			return NULL;
		}
	}

	for(int i = 0; i < num_threads; i++) {
		pthread_join(threads[i], NULL);
	}
	*a_error = NULL;
	free(threads);
	free(args);
	return result;
}

BMPImage* _image_copy(const BMPImage* image_original) {
	BMPImage* a_image_copy = malloc(sizeof(*a_image_copy));
	a_image_copy -> header = image_original -> header;
	unsigned char* data_copy = malloc(image_original -> header.image_size_bytes);
	for(int i = 0; i < image_original -> header.image_size_bytes; i++) {
		data_copy[i] = (image_original -> data)[i];
	}
	a_image_copy -> data = data_copy;
	return a_image_copy;
}

/*

BMPImage* binarize(const BMPImage*image_original, int radius, int num_thread, const char** a_error) {
	BMPImage* a_image_copy = malloc(sizeof(*a_image_copy));
	a_image_copy -> header = image_original -> header;
	unsigned char* data_copy = malloc(image_original -> header.image_size_bytes);
	for(int i = 0; i < image_original -> header.image_size_bytes; i++) {
		data_copy[i] = (image_original -> data)[i];
	}
	a_image_copy -> data = data_copy;

	int row_size = image_original -> header.image_size_bytes / image_original -> header.height_px;
	for(int a = 0; a < image_original -> header.height_px; a++) {
		for(int i = 0; i < image_original -> header.width_px; i++) {
			int neighbor_size = 0;
			int right_num = 0;
			int upper_num = 0;
			int lower_num = 0;
			int left_num  = 0;
			int neighbor_num = 0;
			int pixel_size = _get_pixel_rgb(image_original, i * BYTESPERPIXEL + a * row_size);

			if(i - radius < 0) {                                                      // add left pixels
				for(int j = 0; j < i; j++) {
					neighbor_size += _add_pixel(image_original, j, a);
					left_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i - j - 1, a);
					left_num++;
				}
			}

			if(i + radius > image_original -> header.width_px - 1) {                  // add right pixels
				for(int j = 0; j < image_original -> header.width_px - i - 1; j++) {
					neighbor_size += _add_pixel(image_original, i + j + 1, a);
					right_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i + j + 1, a);
					right_num++;
				}
			}

			if(a - radius < 0) {                                                      //add lower pixels
				for(int j = 0; j < a; j++) {
					neighbor_size += _add_pixel(image_original, i, j);
					lower_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i, a - j - 1);
					lower_num++;
				}
			}

			if(a + radius > image_original -> header.height_px - 1) {                 //add upper pixels
				for(int j = 0; j < image_original -> header.height_px - a - 1; j++) {
					neighbor_size += _add_pixel(image_original, i, a + j + 1);
					upper_num++;
				}
			} else {
				for(int j = 0; j < radius; j++) {
					neighbor_size += _add_pixel(image_original, i, a + j + 1);
					upper_num++;
				}
			}

			for(int y = 0; y < upper_num; y++) {                                      //add upper left and right pixels
				for(int x = 0; x < left_num; x++) {
					neighbor_size += _add_pixel(image_original, i - x - 1, a + y + 1);
				}
				for(int x = 0; x < right_num; x++) {
					neighbor_size += _add_pixel(image_original, i + x + 1, a + y + 1);
				}
			}

			for(int y = 0; y < lower_num; y++) {                                      //add lower left and right pixels
				for(int x = 0; x < left_num; x++) {
					neighbor_size += _add_pixel(image_original, i - x - 1, a - y - 1);
				}
				for(int x = 0; x < right_num; x++) {
					neighbor_size += _add_pixel(image_original, i + x + 1, a - y - 1);
				}
			}
			neighbor_num = lower_num + upper_num + left_num + right_num
				+ upper_num * (left_num + right_num)
				+ lower_num * (left_num + right_num);
			//neighbor_size -= 200;

			if(pixel_size * neighbor_num <= neighbor_size) {
				a_image_copy -> data[a * row_size + i * BYTESPERPIXEL] = BLACK;	
				a_image_copy -> data[a * row_size + i * BYTESPERPIXEL + 1] = BLACK;	
				a_image_copy -> data[a * row_size + i * BYTESPERPIXEL + 2] = BLACK;	
			} else {
				a_image_copy -> data[a * row_size + i * BYTESPERPIXEL] = WHITE;	
				a_image_copy -> data[a * row_size + i * BYTESPERPIXEL + 1] = WHITE;	
				a_image_copy -> data[a * row_size + i * BYTESPERPIXEL + 2] = WHITE;		
			}
		}
	}
	return a_image_copy;
}
*/
int _add_pixel(const BMPImage* image, int i, int a) {
	return _get_pixel_rgb(image, (image -> header.height_px - a) * image -> header.image_size_bytes / image -> header.height_px + i * BYTESPERPIXEL);
}

int _get_pixel_rgb(const BMPImage* image, int index) {
	return image -> data[index + 0]
		+ image -> data[index + 1] 
		+ image -> data[index + 2];
}

/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab:*/
