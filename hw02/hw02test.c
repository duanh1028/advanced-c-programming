#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "hw02.h"
int main(int argc, char* argv[]) {

	print_integer(165, 16, "");
    printf("\n");

	print_integer(-9, 2, "0x");
    printf("\n");

	print_integer(INT_MIN, 2, "0x");
    printf("\n");
	
	print_integer(70, 36, "0b");
    printf("\n");

	print_integer(21, 17, "0x");
    printf("\n");

	print_integer(-8, 3, "0x");
    printf("\n");
	return EXIT_SUCCESS;
}
 
