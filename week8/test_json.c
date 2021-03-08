#include<stdio.h>
#include<stdbool.h>
#include<assert.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "json.h"

int main(int argc, char*argv[]) {
	char* a_pos = "\"abc\n123\"";

	Element element;
	bool result = parse_element(&element, &a_pos);
	printf("the string is %d, and the result is %d", element.value.as_string, result);
	if(result) {
		free_element(element);
	}
	return EXIT_SUCCESS;
}

