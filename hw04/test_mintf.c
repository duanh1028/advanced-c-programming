#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "mintf.h"

int main(int argc, char* argv[]) {

    mintf("My favorite number is %$\n", -1413.336);
	mintf("\nmy name is %s and %d\n", "darren", 8);
	mintf("\nnumber %d written ;in binary is %x\n", -1234, -1234);
	mintf("\n%%%s%\n9", "dingyujie%");
	
	return EXIT_SUCCESS;
}
