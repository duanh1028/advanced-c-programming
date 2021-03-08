#include<errno.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<limits.h>
#include "bmp.h"
#include "miniunit.h"

const int header_size = 54;
const int dib_header_size = 40;
const int bits_per_pixel = 24;
const int magic_value = 0x4d42;
const int num_of_planes = 1;
const int compression = 0;
const int num_of_colors = 0;
const int important_colors = 0;
const int bytes_per_pixel = 3;
const int reserved_value = 0;
const int resolution_num = 0;
const int padding = 0x00;
const int fourteen = 14;
const int FOUR = 4;
int test_write();
int test_write1();
int test_write2();
int test_read();
int test_read1();
int test_read2();
int test_read3();
int test_read4();
int test_crop();
int test_crop1();
int test_crop2();
int test_crop3();
int _test_get_padding(const BMPHeader* header);
int _test_get_image_size(const BMPHeader* header);
int _test_get_row_size(const BMPHeader* header);
BMPImage* create_bmp(size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b);
void _test_free_bmp(BMPImage* image);
void set_pixel(BMPImage* img, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b);


int main(int argc, char* argv[]) {
	mu_run(test_write);	
	mu_run(test_write1);
	mu_run(test_write2);

	mu_run(test_read);
	mu_run(test_read1);
	mu_run(test_read2);
	mu_run(test_read3);
	mu_run(test_read4);
	
	mu_run(test_crop);
	mu_run(test_crop1);
	mu_run(test_crop2);
	mu_run(test_crop3);
	return EXIT_SUCCESS;
}

int test_crop() {
	mu_start();
	BMPImage* image = create_bmp(99, 100, 0xff, 0x00, 0x80);
	image -> header.image_size_bytes--;
	const char* error = NULL;
	BMPImage* new_image = crop_bmp(image, 50, 50, 50, 50, &error);
	free_bmp(image);
	free_bmp(new_image);
	mu_check((error != NULL));
	mu_end();
}

int test_crop1() {
	mu_start();
	BMPImage* image = create_bmp(100, 100, 0xff, 0x00, 0x80);
	const char* error = NULL;
	BMPImage* new_image = crop_bmp(image, 50, 50, 50, 50, &error);
	_test_free_bmp(image);
	_test_free_bmp(new_image);
	mu_check((error == NULL));
	mu_end();
}

int test_crop2() {
	mu_start();
	BMPImage* image = NULL;
	const char* error = NULL;
	BMPImage* new_image = crop_bmp(image, 50, 50, 50, 50, &error);
	_test_free_bmp(image);
	_test_free_bmp(new_image);
	mu_check((error != NULL));
	mu_end();
}


int test_crop3() {
	mu_start();
	BMPImage* before_crop = create_bmp(100, 100, 0xff, 0x00, 0x80);
	BMPImage* after_crop = create_bmp(50, 50, 0xff, 0x00, 0x80);
	const char* error = NULL;
	BMPImage* new_crop = crop_bmp(before_crop, 50, 50, 50, 50, &error);
	bool check = true;
	if(memcmp(&new_crop -> header, &after_crop -> header, sizeof(BMPHeader)) != 0) {
		check = false;
	}
	int times = memcmp(&new_crop -> header, &after_crop -> header, sizeof(new_crop -> header.image_size_bytes));
	printf("the memcmp is%d", times);
	for(int i = 0; i < (new_crop -> header.image_size_bytes); i++) {
//		printf("%d times it has passed\n", times++);
		if(new_crop -> data[i] != after_crop -> data[i]) {
			check = false;
		}
	}
	_test_free_bmp(before_crop);
	_test_free_bmp(after_crop);
	_test_free_bmp(new_crop);
	mu_check(check);
	mu_end();
}





int test_read() {
	mu_start();	
	FILE* fp = NULL;
	const char* error = NULL;
	BMPImage* temp = read_bmp(fp, &error);
	_test_free_bmp(temp);
	mu_check((error != NULL));
	mu_end();
}

int test_read1() {
	mu_start();
	BMPImage* image = create_bmp(100, 100, 0xff, 0x00, 0x80);
	image -> header.image_size_bytes --;
	FILE* fp_write = fopen("file.bmp", "w");	
	fwrite(&image -> header, sizeof(BMPHeader), 1, fp_write);
	fwrite(image -> data, sizeof(*(image -> data)), image -> header.image_size_bytes, fp_write);
	_test_free_bmp(image);
	fclose(fp_write);
	FILE* fp_read = fopen("file.bmp", "r");
	const char* error = NULL;
	BMPImage* image_read = read_bmp(fp_read, &error);
	mu_check((error != NULL));
	_test_free_bmp(image_read);
	fclose(fp_read);
	mu_end();
}

int test_read2() {
	mu_start();
	BMPImage* image = create_bmp(100, 100, 0xff, 0xc0, 0xcb);
	FILE* fp_write = fopen("file.bmp", "w");
	fwrite(&image -> header, sizeof(BMPHeader), 1, fp_write);
	fwrite(image -> data, sizeof(*(image -> data)), image -> header.image_size_bytes, fp_write);
	_test_free_bmp(image);
	fclose(fp_write);
	FILE* fp_read = fopen("file.bmp", "r");
	const char* error = NULL;
	BMPImage* image_read = read_bmp(fp_read, &error);
	mu_check((error == NULL));
	_test_free_bmp(image_read);
	fclose(fp_read);
	mu_end();
}

int test_read3() {
	mu_start();
	BMPImage* image = create_bmp(100, 100, 0xff, 0x00, 0x80);
	FILE* fp_write = fopen("file.bmp", "w");
	fwrite(&image -> header, sizeof(BMPHeader), 1, fp_write);
	_test_free_bmp(image);
	fclose(fp_write);
	FILE* fp_read = fopen("file.bmp", "r");
	const char* error = NULL;
	BMPImage* image_read = read_bmp(fp_read, &error);
	mu_check((error != NULL));
	_test_free_bmp(image_read);
	fclose(fp_read);
	mu_end();
}

int test_read4() {
	mu_start();
	FILE* fp_write = fopen("file.bmp", "w");
	fwrite("ECE 264 sucks", sizeof(char), fourteen, fp_write);
	fclose(fp_write);
	FILE* fp_read = fopen("file.bmp", "r");
	const char* error = NULL;
	BMPImage* image_read = read_bmp(fp_read, &error);
	mu_check((error != NULL));
	_test_free_bmp(image_read);
	fclose(fp_read);
	mu_end();
}



int test_write() {
	mu_start();
	BMPImage* image = create_bmp(99, 100, 0xff, 0xc0, 0xcb);
	set_pixel(image, 1, 1, 0xff, 0xff, 0xff);
	FILE* fp = fopen("file.bmp", "w");
	const char* error = NULL;
	write_bmp(fp, image, &error);
	mu_check((error == NULL));
	_test_free_bmp(image);
	fclose(fp);
	mu_end();
}

int test_write1() {
	mu_start();
	BMPImage* image = create_bmp(100, 100, 0xff, 0x00, 0x80);
	FILE* fp = NULL;
	const char* error = NULL;
	write_bmp(fp, image, &error);
	mu_check((error != NULL));
	_test_free_bmp(image);
	mu_end();
}

int test_write2() {
	mu_start();
	BMPImage* image = NULL;
	FILE* fp = fopen("file.bmp", "w");
	const char* error = NULL;
	write_bmp(fp, image, &error);
	mu_check((error != NULL));
	fclose(fp);
	mu_end();
}

int _test_get_image_size(const BMPHeader* header) {
	return _test_get_row_size(header) * header -> height_px;
}
int _test_get_row_size(const BMPHeader* header) {
	return header -> width_px * bytes_per_pixel + _test_get_padding(header);
}
int _test_get_padding(const BMPHeader* header) {
	return (FOUR - (header -> width_px * bytes_per_pixel) % FOUR ) % FOUR;
}
BMPImage* create_bmp(size_t w, size_t h, uint8_t r, uint8_t g, uint8_t b) {
	BMPImage* image = malloc(sizeof(*image));
	image -> header.type = magic_value;
	image -> header.reserved1 = reserved_value;
	image -> header.reserved2 = reserved_value;
	image -> header.offset = header_size;
	image -> header.dib_header_size = dib_header_size;
	image -> header.width_px = w;
	image -> header.height_px = h;
	image -> header.num_planes = num_of_planes;
    image -> header.bits_per_pixel = bits_per_pixel;
	image -> header.compression = compression;
	image -> header.x_resolution_ppm = resolution_num;
	image -> header.y_resolution_ppm = resolution_num;
	image -> header.num_colors = num_of_colors;
	image -> header.important_colors = important_colors;	
	image -> header.image_size_bytes = _test_get_image_size((const BMPHeader*)&image -> header);
	image -> header.size = header_size + image -> header.image_size_bytes;
	image -> data = malloc(image -> header.image_size_bytes);
	int image_index = 0;	
	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			image -> data[image_index++] = r;
			image -> data[image_index++] = g;
			image -> data[image_index++] = b;
		}
		for(int a = 0; a < _test_get_padding((const BMPHeader*)&image -> header); a++) {
			image -> data[image_index++] = padding;
		}
	}
	return image;
}

void _test_free_bmp(BMPImage* image) {
	if(image != NULL && image -> data != NULL) {	
		free(image -> data);
		free(image);
	} else if(image != NULL && image -> data == NULL) {
		free(image);
	}
}

void set_pixel(BMPImage* img, size_t x, size_t y, uint8_t r, uint8_t g, uint8_t b) {
	int index = 0;
	for(int i = 0; i < y; i++) {
		for(int j = 0; j < (img -> header.width_px - x) * bytes_per_pixel + 1; j++) {
			index++;
		}
		if(i != y) {
		index += _test_get_padding((const BMPHeader*)&img -> header);
		}
	}
	img -> data[index++] = r;
	img -> data[index++] = g;
	img -> data[index++] = b;
}









