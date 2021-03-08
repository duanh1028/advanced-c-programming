#include<stdio.h>
#include<stdlib.h>

void print(char** value, char** a_value) {
	if(**a_value != '\"') {
		printf("it has a passed here");
	}
	int i = 1;
	(*a_value)++;
	while(**a_value != '\0') {
		if(**a_value == '\n') {
			printf("it is false");
		}

		if(**a_value == '\"') {
			(*a_value) -= i;
			(*value) = *a_value;
		}
		(*a_value)++;
		i++;
	}
}

int main() {
	char *string  = "\"abc\"";
	char *value;
	print(&value, &string);
	
	return EXIT_SUCCESS;
}


