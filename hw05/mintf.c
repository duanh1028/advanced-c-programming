#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include "mintf.h"
#define NUMBER 48
#define ALPHABET 87
#define NUMBER_CHECK 9

void mintf(const char *format, ...);
void print_integer(int n, int radix, char* prefix);

void mintf(const char *format, ...) {
	va_list hw;         //declare the va_list
	int i = 0;           //i used in for loop   
	int index = 0;            //index
	double argumentValue;     // double receiver
	int percentSign = 37;      //percentSign
	int integerValue = 0;      //declare the integer value
	int decimalValue = 0;       //declare the decimal value
	char *stringReceiver = 0;     //declare char* data receiver
	int charReceiver = 0;          //declare character data receiveri


	va_start(hw, format);

	while(format[index] != '\0') { 
		if(format[index] == '%') {
			index++;
			if(index != '\0') {
				if(format[index] == '%') {
					fputc(percentSign, stdout);
				}
				else if(format[index] == 'd') {
					print_integer(va_arg(hw, int), 10, "");
				}
				else if(format[index] == 'x') {
					print_integer(va_arg(hw, int), 16, "0x");
				}
				else if(format[index] == 'b') {
					print_integer(va_arg(hw, int), 2, "0b");
				}
				else if(format[index] == 'c') {
					charReceiver = va_arg(hw, int);
					fputc(charReceiver, stdout);
				}
				else if(format[index] == '$') {
					argumentValue = va_arg(hw, double);
					integerValue = (int)argumentValue;
					decimalValue = abs((int)((argumentValue - integerValue) * 100));
					print_integer(integerValue, 10, "$");
					fputc(percentSign + 9, stdout);
					print_integer(decimalValue, 10, "");
				}
				else if(format[index] == 's') {
					stringReceiver = va_arg(hw, char*);
					for(i = 0; stringReceiver[i] != '\0'; i++) {
						fputc(stringReceiver[i], stdout);
					}
				}
				else {
					index--;
					fputc(percentSign, stdout);
				}
			}
		}
		else {
			fputc(format[index], stdout);
		}
		index++;
	}
}

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
			if (remainder > NUMBER_CHECK) {
				remainder += ALPHABET;
			}
			else {	
				remainder += NUMBER;
			}
			fputc(remainder, stdout);
		}
	}
}
