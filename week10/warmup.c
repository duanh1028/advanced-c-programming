#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
void print_contents_of_file(char* filename);
void print_first_n_chars_in_file(char* filename, int n, char** a_error);
char* get_first_line_of_file(char* filename, char** a_error);

void print_contents_of_file(char* filename) {
	FILE* fp = fopen(filename, "r");
	for(char ch = fgetc(fp); !feof(fp); ch = fgetc(fp)) {
		fputc(ch, stdout);
	}
	fclose(fp);
}

void print_first_n_chars_in_file(char* filename, int n, char** a_error) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL || ferror(fp)) {
		fprintf(stderr, "%s", strerror(errno));
		return EXIT_FAILURE;
	} else {
		for(int i = 0; i < n; i++) {
			char ch = fgetc(fp);
			fputc(ch, stdout);
		}
	fclose(fp);
	}
}

char* get_first_line_of_file(char* filename, char** a_error) {
	FILE* fp = fopen(filename, "r");
	if(fp == NULL || ferror(fp)) {
		fprintf(stderr, "%s", strerror(errno));
		return EXIT_FAILURE;
	}
	int length = 0;
	for(char ch = fgetc(fp); ch != '\n'; ch = fgetc(fp)) {
		length++;
	}
	printf("the length is %d\n", length);
	char* str = malloc(sizeof(*str) * (length + 1));
	fseek(fp, 0, SEEK_SET);
	fread(str, sizeof(*str), length, fp);
	str[length] = '\0';
	fclose(fp);
	return str;
}

int main() {
	char* error_message;
	print_contents_of_file("file.txt");
	print_first_n_chars_in_file("file.txt", 5, &error_message);
	char* str = get_first_line_of_file("file.txt", &error_message);
	printf("the str is %s\n", str);
	free(str);
	return EXIT_SUCCESS;
}
