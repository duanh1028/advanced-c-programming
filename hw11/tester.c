#include<stdio.h>
#include "bmp.h"
#include<stdlib.h>
int main() {
	error = 1;
	print();
	FILE* fp = fopen("6x6_24bit.bmp", "r");	
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	BMPHeader* head = malloc(sizeof(*head));
	fread(head, sizeof(BMPHeader), 1, fp);
	BMPImage* bmp = malloc(size);
	*bmp = (BMPImage) {.header = *head, .data = malloc(sizeof(unsigned char) * size - 54)};
	
	printf("type is %d, and the size is %d", bmp -> header.width_px, bmp -> header.height_px);
	fclose(fp);
	return 0;

}

