#include<assert.h>
#include<pthread.h>
#include<stdbool.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "mtat.h"
#include "bmp.h"
/*
void _free_image(BMPImage* image) {
	if(image != NULL) {
		free(image -> data);
	}
	free(image);
}*/


int main(int argc, char* argv[]) {
	const char* error = NULL;
	FILE* fp_read1 = fopen("img2_384x510_gray.bmp", "r");
	FILE* fp_write1 = fopen("file.bmp", "w");
	BMPImage* image1 = read_bmp(fp_read1, &error);
	BMPImage* binarized_image1 = binarize(image1, 2, 3, &error);
	write_bmp(fp_write1, binarized_image1, &error);
	fclose(fp_write1);
	fclose(fp_read1);
	free_bmp(image1);
	free_bmp(binarized_image1);

	FILE* fp_read2 = fopen("img1_6x6_color.bmp", "r");
	BMPImage* image2 = read_bmp(fp_read2, &error);
	BMPImage* binarized_image2 = binarize(image2, 2, 10000, &error);
	fclose(fp_read2);
	free_bmp(image2);
	free_bmp(binarized_image2);

	BMPImage* binarized_image3 = binarize(NULL, 2, 10000, &error);
	free_bmp(binarized_image3);
/*	
	FILE* fp_read4 = fopen("img2_384x510_gray.bmp", "r");
	BMPImage* image4 = read_bmp(fp_read4, &error);
	BMPImage* binarized_image4 = binarize(image4, 2, 10000, &error);
	fclose(fp_read4);
	free_bmp(image4);
	free_bmp(binarized_image4);*/
	return EXIT_SUCCESS;
}

