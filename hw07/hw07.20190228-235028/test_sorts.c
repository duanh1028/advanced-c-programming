#include "sorts.h"
#include <stdio.h>

int main(int argc, char*argv[]) {
	int array[9] = {4,3,1,5,5,6,7,8,7};
	merge_sort_array(array, 9);
	
	quick_sort_array(array, 9);
	
	tree_sort_array(array, 9);
	for(int i = 0; i < 9; i++) {
		printf("the value is %d\n", array[i]);
	}
	return EXIT_SUCCESS;
}
