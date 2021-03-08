#ifndef __BACKREAD_H_20190325__
#define __BACKREAD_H_20190325__
#include <stdbool.h>
#include <stdio.h>
#define BUFFERSIZE 8
typedef struct {
	FILE* fp_copy;
	unsigned char* arr;
	int offset;
	int bufferLocation;
	int num;
	unsigned char* line;
} FileWrapper;

FileWrapper* create_file_wrapper(char* fileName, char** a_error);
unsigned char* read_line(FileWrapper* fw, char** a_error);
void free_wrapper(FileWrapper* fw);
#endif
