#include <stdio.h>
#include "hw02.h"

void print_integer(int n, int radix, char* prefix) {
	
	int remainder = 0;  //delcare variable remainder
	int count = 0;      //declare variable count
	int copy_of_count = 0;    //declare variable copy_of_count
	unsigned int copy_of_n = n;		//create a copy of n
	unsigned int copy2_of_n = n; 	//create another copy of n
    int idx = 0;        //declare variable idx

	if(n == 0) {
		while(prefix[idx] != '\0') {
			fputc(prefix[idx], stdout);
			idx++;	
		}  
	    fputc('0', stdout);	
	}
	else {
		if(n < 0) {
			copy_of_n = -copy_of_n;    //make positive
			copy2_of_n = -copy2_of_n;
			fputc('-', stdout);
		}
		while(prefix[idx] != '\0') {
			fputc(prefix[idx], stdout);
			idx++;
		}
		while(count != copy2_of_n) {
			copy_of_count = count;
			while(copy_of_n > copy_of_count) {
				remainder = copy_of_n % radix;
				count = copy_of_n;       //reserve the value of copy_of_n
				copy_of_n /= radix;

			}
			copy_of_n = copy2_of_n;
			if (remainder > 9) {
				remainder += 87;
			}
			else {
				remainder += 48;
			}
			fputc(remainder, stdout);
		}
	}
}
