#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include "bmp.h"

int main(int argc, char* argv[]) {
	FILE* fp = fopen("airplane.bmp", "r");
	const char* error = NULL;
	BMPImage* result = read_bmp(fp, &error);
	printf("Error is : %s", error);
	BMPImage* result1 = crop_bmp((const BMPImage*)result, 299, 399, 300, 400, &error);
	FILE* fp1 = fopen("file.bmp", "w");
	const char* write_error = "";
	bool check = write_bmp(fp1, result1, &write_error);
	printf("\n%d", check);
	free_bmp(result1);
	free_bmp(result);
	fclose(fp);
	fclose(fp1);
	return EXIT_SUCCESS;
}
