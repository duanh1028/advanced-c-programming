#include<stdbool.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include "json.h"

bool parse_int(int* a_value, char** a_pos) {
	int i = 0;
	bool neg = false;
	if(**a_pos == '-') {
		i++;
		(*a_pos)++;
		neg = true;
	}
	while(isdigit(**a_pos)) {
		i++;
		(*a_pos)++;
	}
	*a_pos -= i;
	int check = 0;
	if(neg) {
		(*a_pos)++;
		check = 1;
	}
	for(int a = check; a < i; a++) {
		*a_value = *a_value * 10 + (**a_pos - 48);
		(*a_pos)++;
	}

	if(neg) {
		*a_value = -(*a_value);
	}
	return true;
}

bool parse_element(Element* a_element, char** a_pos) {
	bool result;
	while(isspace(**a_pos)) {
		(*a_pos)++;
	}
	if(isdigit(**a_pos) || ((**a_pos == '-') && isdigit(*(*a_pos + 1)))) {
		a_element -> type = ELEMENT_INT;
		a_element -> value.as_int = 0;
		result = parse_int(&a_element -> value.as_int, a_pos);
		return result;
	}
	else if(**a_pos == '"') {
		a_element -> type = ELEMENT_STRING;
		a_element -> value.as_string = "";
		result = parse_string(&a_element -> value.as_string, a_pos);
		return result;
	}
	else if(**a_pos == '[') {
		a_element -> type = ELEMENT_LIST;
		a_element -> value.as_list = NULL;
		return parse_list(&a_element -> value.as_list, a_pos);
	}
	else {
		a_element -> type = ELEMENT_STRING;
		a_element -> value.as_string = NULL;
		return false;
	}
}

bool parse_string(char** a_string, char** a_pos) {
	int length = 0;
	(*a_pos)++;
	while(**a_pos != '\0') {
		if(**a_pos == '\n') {
			return false;    
		}
		if(**a_pos == '\"') {
			char* temp = malloc(sizeof(char) * ++length);
			*a_pos -= (length - 1);
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

bool parse_list(Node** a_head,  char** a_pos) {
	bool if_in_the_string = false;
	int num_of_leftlist = 0;
	int num_of_rightlist = 0;
	Node* tail = NULL;
	for(int i = 0; (*a_pos)[i] != '\0'; i++) {
		if((*a_pos)[i] == '"') {
			if_in_the_string = !if_in_the_string;
		} 
		else if(((*a_pos)[i] == '[') && (!if_in_the_string)) {
			num_of_leftlist++;
		}
		else if(((*a_pos)[i] == ']') && (!if_in_the_string)) {
			num_of_rightlist++;
		}
		else{
		}
	}
	if(num_of_leftlist != num_of_rightlist) {
		return false;
	}
	char* new_pos = "";
	int new_pos_index = 0;
	char* temp_char = malloc(sizeof(temp_char));
	for(int i = 1; (*a_pos)[i] != ']'; i++) {
		if(((*a_pos)[i] == ',') || ((*a_pos)[i] == ']')) {
			new_pos_index = 0;
			new_pos = temp_char; 
			temp_char = NULL;
			Element element;
			bool result = parse_element(&element, &new_pos);
			if(!result) {
				return false;
			}
			Node* temp = malloc(sizeof(*temp));
			temp -> element = element;
			temp -> next = NULL;
			if(*a_head == NULL) {
				*a_head = temp;
				tail = *a_head;
			}
			else {
				tail -> next = temp;
			}
			tail = temp;
			new_pos = "";
			i++;
		}
		temp_char[new_pos_index] = (*a_pos)[i];
		new_pos_index++;
	}
	free(temp_char);
	return true;
}

/*
bool parse_list(Node** a_head, char** a_pos) {
	int size = 0;
	(*a_pos)++;
	while(**a_pos != '\0') {
		if((**a_pos == ',') || (*(*a_pos - 1) == '[')) {
			*a_pos++;
			while(isspace(**a_pos)) {
				*a_pos++;
			}
			if(**a_pos == '"') {
				int length = 0;
				(*a_pos)++;
				while(**a_pos != ",") {
					if(**a_pos == '\n') {
						return false;    
					}
					if(**a_pos == '\"') {
					}
					(*a_pos)++;
					length++;
				}
				return false;
			}
			else if((isdigit(**a_pos) || ((**a_pos == '-') && isdigit(*(*a_pos + 1))))) {

			}
			else {
				return false;
			}
		}

	}
	return false;
}
*/

void free_element(Element element) {
	if(element.type == ELEMENT_STRING) {
		if(element.value.as_string != NULL) {
			free(element.value.as_string);
		}
	}
}

void print_element(Element element) {
	if(element.type == ELEMENT_INT) {
		printf("%d", element.value.as_int);
	}
	else if(element.type == ELEMENT_STRING) {
		printf("%s", element.value.as_string);
	}
	else {
	}
}

						
