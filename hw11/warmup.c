#include<errno.h>
#include<assert.h>
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>

int main() {
	return EXIT_SUCCESS;
}



typedef struct {int x; int y;} Point;
char* read_file(const char* path, const char** a_error) {
	FILE* fp = fopen(path, "r");
	*a_error = NULL;
	if(fp == NULL || ferror(fp)) {
		*a_error = strerror(errno);
		return NULL;
	} 
	else {
		fseek(fp, 0, SEEK_END);
		int size = ftell(fp);
		char* str = malloc(sizeof(* str) * size + 1);
		fseek(fp, 0, SEEK_SET);
		fread(str, sizeof(*str), size, fp);
		str[size] = '\0';
		fclose(fp);
		return str;
	}
}

void write_file(const char* path, const char* contents, const char** a_error) {
	FILE* fp = fopen(path, "w");	
	if(fp == NULL || ferror(fp)) {
		*a_error = strerror(errno);
	} 
	else {
		fwrite(contents, sizeof(*contents), (int)strlen(contents), fp);
		fclose(fp);
	}
}

void write_point(const char* path, Point p, const char** a_error) {
	FILE* fp = fopen(path, "w");
	*a_error = NULL;	
	if(fp == NULL || ferror(fp)) {
		*a_error = strerror(errno);
	}
	else {
		fwrite(&p, sizeof(p), 1, fp);
		fclose(fp);
	}
}

Point read_point(const char* path, const char** a_error) {
	FILE* fp = fopen(path, "r");
	*a_error = NULL;
	Point new_point = {.x = 0, .y = 0};
	if(fp == NULL || ferror(fp)) {
		*a_error = strerror(errno);
		return new_point;
	}
	fread(&new_point, sizeof(new_point), 1, fp);
	fclose(fp);
	return new_point;
}
