#include<stdio.h>
#include<stdbool.h>
#include<ctype.h>
#include<stdlib.h>
#include "json.h"

int main(int argc, char*argv[]) {
	char* a_pos = "-123";
	Element element; 
	parse_element(&element, &a_pos);
	print_element(element);
	free_element(element);
	
	a_pos = "[123]";
	Element element1;
	parse_element(&element1, &a_pos);
	print_element(element1);
	free_element(element1);
	
	a_pos = "......";
	Element element2;
	parse_element(&element2, &a_pos);
	print_element(element2);
	free_element(element2);

	a_pos = "";
	Element element3;
	parse_element(&element3, &a_pos);
	print_element(element3);
	free_element(element3);

	a_pos = "  \"avasw1\"";
	Element element4;
	parse_element(&element4, &a_pos);
	print_element(element4);
	free_element(element4);

	a_pos = "\"1212\nadas\"";
	Element element5;
	parse_element(&element5, &a_pos);
	print_element(element5);
	free_element(element5);

	
	a_pos = "\"adawd";
	Element element6;
	parse_element(&element6, &a_pos);
	print_element(element6);
	free_element(element6);
	
	a_pos = "123adw";
	Element element7;
	parse_element(&element7, &a_pos);
	print_element(element7);
	free_element(element7);
	return EXIT_SUCCESS;
}

