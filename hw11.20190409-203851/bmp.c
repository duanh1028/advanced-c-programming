#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include "bmp.h"
#define HEADERSIZE 54
#define DIBHEADERSIZE 40
#define BITSPERPIXEL 24
#define MAGICVALUE 0x4d42
#define NUMOFPLANES 1
#define COMPRESSION 0
#define NUMOFCOLORS 0
#define IMPORTANTCOLORS 0
#define BYTESPERPIXEL 3
const char* header_error = "Invalid header!!!";
const char* write_header_error = "Cannot write the header into the file!!!";
const char* read_header_error = "Can't read the header!!!";
const char* read_data_error = "Can't read the data!!!";
const char* memory_error = "There isn't enough memory for malloc!!!";
const char* write_data_error = "Cannot write data into the file!!!";
long _get_file_size(FILE* fp);
int _get_padding(const BMPHeader* header);
int _get_row_size(const BMPHeader* header);
int _get_image_size(const BMPHeader* header);
BMPImage* read_bmp(FILE* fp, const char** a_error) {
	fseek(fp, 0, SEEK_SET);
	if(fp == NULL || ferror(fp)) {
		*a_error = strerror(errno);
		return NULL;
	}
	BMPImage* bmp = malloc(sizeof(*bmp));
	fread(&bmp -> header, HEADERSIZE, 1, fp);
	if(check_bmp_header((const BMPHeader*)&bmp -> header, fp)) {
		bmp -> data = malloc(sizeof(unsigned char) * bmp -> header.image_size_bytes);
		fread(bmp -> data, sizeof(unsigned char) * bmp -> header.image_size_bytes, 1, fp);
	} else {
		*a_error = header_error;
		free(bmp);
		return NULL;
	}
	return bmp;
}
bool check_bmp_header(const BMPHeader* bmp_hdr, FILE* fp) {
	if(fp == NULL) {
		return bmp_hdr -> type == MAGICVALUE &&
			bmp_hdr -> offset == HEADERSIZE &&
			bmp_hdr -> dib_header_size == DIBHEADERSIZE &&
			bmp_hdr -> num_planes == NUMOFPLANES &&
			bmp_hdr -> compression == COMPRESSION &&
			bmp_hdr -> num_colors == NUMOFCOLORS &&
			bmp_hdr -> important_colors == IMPORTANTCOLORS &&
			bmp_hdr -> bits_per_pixel == BITSPERPIXEL &&
			_get_image_size(bmp_hdr) == bmp_hdr -> image_size_bytes;
	} else {
		return bmp_hdr -> type == MAGICVALUE &&
			bmp_hdr -> offset == HEADERSIZE &&
			bmp_hdr -> dib_header_size == DIBHEADERSIZE &&
			bmp_hdr -> num_planes == NUMOFPLANES &&
			bmp_hdr -> compression == COMPRESSION &&
			bmp_hdr -> num_colors == NUMOFCOLORS &&
			bmp_hdr -> important_colors == IMPORTANTCOLORS &&
			bmp_hdr -> bits_per_pixel == BITSPERPIXEL &&
			_get_image_size(bmp_hdr) == bmp_hdr -> image_size_bytes &&
			bmp_hdr -> size == _get_file_size(fp);
	}
}
long _get_file_size(FILE* fp) {
	long currentPosition = ftell(fp);
	fseek(fp, 0, SEEK_END);
	long lastPosition = ftell(fp);
	fseek(fp, currentPosition, SEEK_SET);
	return lastPosition;
}
int _get_image_size(const BMPHeader* header) {
	return _get_row_size(header) * header -> height_px;
}
int _get_row_size(const BMPHeader* header) {
	int row_size_no_padding = header -> width_px * BYTESPERPIXEL;
	return row_size_no_padding + _get_padding(header);
}
int _get_padding(const BMPHeader* header) {
	return (4 - (header -> width_px * BYTESPERPIXEL) % 4) % 4;
}
bool write_bmp(FILE* fp, BMPImage * image, const char** a_error) {
	fseek(fp, 0, SEEK_SET);
	if(fp == NULL || ferror(fp)) {
		*a_error = strerror(errno);
		return NULL;
	}
	if(image == NULL || !check_bmp_header((const BMPHeader*)&image -> header, NULL)) {
		*a_error = header_error;
		return false;	
	}
	fwrite(&image -> header, sizeof(BMPHeader), 1, fp);
	fwrite(image -> data, sizeof(*(image -> data)), image -> header.image_size_bytes, fp);
	return true;
}
void free_bmp(BMPImage* image) {
	if(image != NULL) {
		free(image -> data);
	}
	free(image);
}
BMPImage* crop_bmp(const BMPImage* image, int x, int y, int w, int h, const char** a_error) {
	if(image == NULL || !check_bmp_header((const BMPHeader*)&image -> header, NULL)) {
		*a_error = header_error;
		return NULL;	
	}
	BMPImage* new_image = malloc(sizeof(*new_image));
	new_image -> header = image -> header;
	new_image -> header.width_px = w;
	new_image -> header.height_px = h;
	new_image -> header.image_size_bytes = _get_image_size((const BMPHeader*)&new_image -> header);
	new_image -> header.size = new_image -> header.image_size_bytes + BMP_HEADER_SIZE;
	new_image -> data = malloc(new_image -> header.image_size_bytes);
	int new_image_index = 0;
	for(int j = h; j > 0; j--) {
		int index = (image -> header.height_px - j) * _get_row_size((const BMPHeader*)&image -> header);
		for(int i = 0; i < w * BYTESPERPIXEL; i++) {
			printf("the i is %d, and j is %d and the number is%d and the index is%d\n", i, j, image -> data[index], index);
			new_image -> data[new_image_index++] = image -> data[index++];
		}
		for(int a = 0; a < _get_padding((const BMPHeader*)&new_image -> header); a++) {
			new_image -> data[new_image_index++] = 0x00;
		}
	}
	return new_image;
}

