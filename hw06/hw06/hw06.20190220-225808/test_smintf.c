#include<limits.h>
#include<stdarg.h>
#include<stdio.h>
#include<stdlib.h>
#include"smintf.h"

int main(int argc, char* argv[]) {
	char* t = smintf("My favorite numb%ser is %$\n%","Max is sb", -1413.09);
	for(int i = 0; t[i] != '\0'; i++) {
		fputc(t[i], stdout);
	}

	free(t);
	
	mintf("My favorite number is %$\n", -1413.336);

	return EXIT_SUCCESS;
}
