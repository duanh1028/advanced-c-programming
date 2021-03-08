#include<stdarg.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>
#define HW06_BONUS

void _print_out(char output) {
	fputc(output, stdout);
}

void _print_integer(int n, int radix, char* prefix, int* str_number, int check, char* result_string, int* i) {
	int remainder = 0;
	int count = 0;
	int copy_of_count = 0;
	unsigned int copy_of_n = n;
	unsigned int copy2_of_n = n;
	int idx = 0;

	if(n == 0) {
		while(prefix[idx] != '\0') {
			if(check == 1) {
				(*str_number)++;
			}
			else if(check == 3) {
				_print_out(prefix[idx]);
			}
			else {
				result_string[(*i)++] = prefix[idx];
			}
			idx++;
		}
		if(check == 1) {
			(*str_number)++;
		}
		else if(check == 3) {
			_print_out('0');
		}
		else {
			result_string[(*i)++] = '0';
		}
	}
	else {
		if(n < 0) {
			copy_of_n = -copy_of_n;
			copy2_of_n = -copy2_of_n;
			if(check == 1) {
				(*str_number)++;
			}
			else if(check == 3) {
				_print_out('-');
			}
			else {
				result_string[(*i)++] = '-';
			}
		}
		while(prefix[idx] != '\0') {
			if(check == 1) {
				(*str_number)++;
			}
			else if(check == 3) {
				_print_out(prefix[idx]);
			}
			else {
				result_string[(*i)++] = prefix[idx];
			}
			idx++;
		}
		while(count != copy2_of_n) {
			copy_of_count = count;
			while(copy_of_n > copy_of_count) {
				remainder = copy_of_n % radix;
				count = copy_of_n;
				copy_of_n /= radix;
			}
			copy_of_n = copy2_of_n;
			if(remainder > 9) {
				remainder += 87;
			}
			else {
				remainder += 48;
			}
			if(check == 1) {
				(*str_number)++;
			}
			else if(check == 3) {
				_print_out(remainder);
			}
			else {
				result_string[(*i)++] = (int)remainder;
			}
		}
	}
}	

int _s_mintf_helper(va_list args, int check, const char* format, char* result_string ) {
	int i = 0;
	int index = 0;
	double argumentValue = 0;
	int integerValue = 0;
	int decimalValue = 0;
	char* stringReceiver;
	int charReceiver;
	int str_number = 0;
	int integerReceiver = 0;
	
	while(format[index] != '\0') {
		if(format[index] == '%') {
			index++;
			if(format[index] != '\0') {
				if(format[index] == '%') {
					if(check == 1) {
						str_number++;
					}
					else if(check == 3) {
						_print_out('%');
					}
					else {
						result_string[i++] = '%';
					}
				}
				else if(format[index] == 'd') {
					integerReceiver = va_arg(args, int);
					if(check == 1) {
						_print_integer(integerReceiver, 10, "", &str_number, check, NULL, NULL);
					}
					else if(check == 3) {
						_print_integer(integerReceiver, 10, "", NULL, check, NULL, NULL);
					}
					else {
						_print_integer(integerReceiver, 10, "", NULL, check, result_string, &i);
					}
				}
				else if(format[index] == 'x') {
					integerReceiver = va_arg(args, int);
					if(check == 1) {
						_print_integer(integerReceiver, 16, "0x", &str_number, check, NULL, NULL);
					}
					else if(check == 3) {
						_print_integer(integerReceiver, 16, "0x", NULL, check, NULL, NULL);
					}
					else {
						_print_integer(integerReceiver, 16, "0x", NULL, check, result_string, &i);
					}
				}
				else if(format[index] == 'b') {
					integerReceiver = va_arg(args, int);
					if(check == 1) {
						_print_integer(integerReceiver, 2, "0b", &str_number, check, NULL, NULL);
					}
					else if(check == 3) {
						_print_integer(integerReceiver, 2, "0b", NULL, check, NULL, NULL);
					}
					else {
						_print_integer(integerReceiver, 2, "0b", NULL, check, result_string, &i);
					}
				}
				else if(format[index] == 'c') {
					charReceiver = va_arg(args, int);
					if(check == 1) {
						str_number++;
					}
					else if(check == 3) {
						_print_out(charReceiver);
					}
					else {
						result_string[i++] = charReceiver;
					}
				}
				else if(format[index] == '$') {
					argumentValue = va_arg(args, double);
					integerValue = (int)argumentValue;
					decimalValue = abs((int)((argumentValue - integerValue) * 100));
					if(check == 1) {
						_print_integer(integerValue, 10, "$", &str_number, check, NULL, NULL);
						str_number++;
						_print_integer(decimalValue, 10, "", &str_number, check, NULL, NULL);
					}
					else if(check == 3) {
						_print_integer(integerValue, 10, "$", NULL, check, NULL, NULL);
						_print_out('.');
						_print_integer(decimalValue, 10, "", NULL, check, NULL, NULL);
					}
					else {
						_print_integer(integerValue, 10, "$", NULL, check, result_string, &i);
						result_string[i++] = '.';
						_print_integer(decimalValue, 10, "", NULL, check, result_string, &i);
					}
				}
				else if(format[index] == 's') {
					stringReceiver = va_arg(args, char*);
					for(int a = 0; stringReceiver[a] != '\0'; a++) {
						if(check == 1) {
							str_number++;
						}
						else if(check == 3) {
							_print_out(stringReceiver[a]);
						}
						else {
							result_string[i++] = stringReceiver[a];
						}
					}
				}
				else {
					index--;
					if(check == 1) {
						str_number++;
					}
					else if(check == 3) {
						_print_out('%');
					}
					else {
						result_string[i++] = '%';
					}
				}
			}
			else {
				if(check == 1) {
					str_number++;
				}
				else if(check == 3) {
					_print_out('%'); 
				}
				else {
					result_string[i++] = '%';
				}
			}
		}
		else {
			if(check == 1) {
				str_number++;
			}
			else if(check == 3) {
				_print_out(format[index]);
			}
			else {
				result_string[i++] = format[index];
			}
		}
		index++;
	}
	return str_number;
}

char* smintf(const char* format, ...) {
	va_list args_orig, copy_of_args, copy2_of_args;
	int str_number = 0;
	va_start(args_orig, format);
	va_copy(copy_of_args, args_orig);
	va_copy(copy2_of_args, args_orig);
	str_number = _s_mintf_helper(copy_of_args, 1, format, NULL);
	char* result_string = malloc(sizeof(char) * ++str_number);
	_s_mintf_helper(copy2_of_args, 2, format, result_string);
	result_string[--str_number] = '\0';
	va_end(args_orig);
	va_end(copy_of_args);
	va_end(copy2_of_args);
	return result_string;
}

void mintf(const char* format, ...) {
	va_list args_orig;
	va_start(args_orig, format);
	_s_mintf_helper(args_orig, 3, format, NULL);
	va_end(args_orig);
}
