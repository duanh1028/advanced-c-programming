#include<stdbool.h>
#include<stdio.h>
#include<assert.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include "json.h"

bool parse_int(int* a_value, char** a_pos) {
	*a_value = 0;
	if(isdigit(**a_pos)) {
		(*a_pos)++;
		if(!isdigit(**a_pos)) {
			return false;
		}
		else {
			(*a_pos)--;
			while(isdigit(**a_pos)) {
				*a_value = *a_value * 10 + (**a_pos - 48);
				(*a_pos)++;
			}
			if(*a_pos[0] == '-') {
				*a_value = -(*a_value);
			}
			return true;
		}
	}
	else {
		return false;
	}
}
/*
   bool parse_list(Node** a_head, char** a_pos) {
   if(**a_pos == '[') {
 *a_pos++;
 }
 if(**a_pos == ']') {
 return true;
 }
 if(**a_pos == '\0') {
 free_element();
 return false;
 }
 int length = 0;
 while(**a_pos != ',') {
 *a_pos++;
 length++;
 }





 }
 */
bool parse_element(Element* a_element, char** a_pos) {
	while(isspace(**a_pos)) {
		(*a_pos)++;
	}
	if(isdigit(**a_pos) || ((**a_pos == '-') && (*(*a_pos + 1)))) {
		a_element -> type = ELEMENT_INT;
		return parse_int(&a_element -> value.as_int, a_pos);
	}
	else if(**a_pos == '"') {
		a_element -> type = ELEMENT_STRING;
		return parse_string(&a_element -> value.as_string, a_pos);
	}
	//	else if(**a_pos == '[') {
	//		a_element -> type = ELEMENT_LIST;
	//		return parse_list(&a_element -> value.as_list, a_pos);
	//	}
	else {
		return false;
	}
}

bool parse_string(char** a_string, char** a_pos) {
	if(**a_pos != '\"'){
		return false;
	}
	int length = 2;
	(*a_pos)++;
	while(**a_pos != '\0') {
		if(**a_pos == '\n') {
			return false;    
		}
		if(**a_pos == '\"') {
			char* temp = malloc(sizeof(char) * ++length);
			*a_pos -= (length - 2);
			for(int i = 0; i < length - 1; i++) {
				temp[i] = **a_pos;
				(*a_pos)++;
			}
			temp[length - 1] = '\0';
			*a_string = temp;
			return true;
		}
		(*a_pos)++;
		length++;
	}
	return false;
}

void free_element(Element element) {
	if(element.type == ELEMENT_STRING) {
		free(element.value.as_string);
	}
}

void print_element(Element element) {
	if(element.type == ELEMENT_INT) {
		printf("%d", element.value.as_int);
	}
	else if(element.type == ELEMENT_STRING) {
		printf("\"%s\"", element.value.as_string);
	}
	else {
	}
}

