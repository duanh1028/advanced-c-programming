#include<stdio.h>
#include<stdlib.h>
#include "backwards_file.h"

int main() {
	char* error;
	FileWrapper* t1 = create_file_wrapper("file.txt", &error);
	printf("%s",read_line(t1, &error));
	free_wrapper(t1);
	return 0;
}
