#include<stdbool.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "backwards_file.h"

FileWrapper* create_file_wrapper(char* filename, char** a_error) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL || ferror(fp)) {
		fprintf(stderr, "%s", strerror(errno));
	}
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	int num = size / BUFFERSIZE + 1;
	FileWrapper* a_file = malloc(size + BUFFERSIZE * num);
	*a_file =(FileWrapper) {
		.arr = malloc(BUFFERSIZE * num),
		.fp_copy = fp,
		.offset = 0,
		.bufferLocation = 0,
		.num = num,
		.line = malloc(sizeof(char)),
	};
	return a_file;
}
unsigned char* read_line(FileWrapper* fw, char** a_error) {
	int num_of_read = 0;
	bool Break = true;
	int lineSize = 0;
	if(fw -> bufferLocation != 0) {
		lineSize += fw -> bufferLocation - 1;
		printf("the bufferLocation is %d\n", fw-> bufferLocation);
	}
	if(fw -> offset != 0) {
		lineSize++;
	}
	int secondCopyOffset = fw -> offset;
	fseek(fw -> fp_copy, -(fw -> offset + 1) * BUFFERSIZE, SEEK_END);
	while(((num_of_read) < (fw -> num)) && (Break)) {
		fread(fw -> arr + ((fw -> offset)++) * BUFFERSIZE, sizeof(char), BUFFERSIZE, fw -> fp_copy);
		fw -> bufferLocation = 0;
		fseek(fw -> fp_copy, - 2 * BUFFERSIZE, SEEK_CUR);
		num_of_read++;
		while((fw -> bufferLocation < 8) && (Break)) {
			(fw -> bufferLocation)++;
			if((fw -> arr + ((fw -> offset) - 1) * BUFFERSIZE)[fw -> bufferLocation] == '\n') {
				if(fw -> bufferLocation < 8) {
					(fw -> bufferLocation)++;
				}
				if(!(fw -> offset == 1 && fw -> bufferLocation == 8)) {
					Break = false;
				}
			}
		}
	}
	int copyOffset = fw -> offset - 1;
	int bufferCopy = fw -> bufferLocation;
	lineSize += BUFFERSIZE * (copyOffset - secondCopyOffset + 1) - bufferCopy;
//	printf("Line size is %d and the buffer is %s and right now the number is", lineSize - 1, fw -> arr);
	free(fw-> line);
	fw-> line = malloc(sizeof(unsigned char*) * lineSize + 1);

	for(int i = 0; i < lineSize; i++) {
		fw -> line[i] = (fw -> arr + (copyOffset) * BUFFERSIZE)[(bufferCopy)++];
		if(bufferCopy == BUFFERSIZE + 1) {
			copyOffset--;
			bufferCopy = 0;
			i--;
		}
		if((fw -> arr + (copyOffset) * BUFFERSIZE)[bufferCopy] == '\n') {
			bufferCopy++;
		}
	}
	fw -> line[lineSize - 1] = '\0';
	return fw -> line;
}
void free_wrapper(FileWrapper* fw) {
	free(fw -> line);
	free(fw -> arr);
	fclose(fw -> fp_copy);
	free(fw);
}
