/* vim: set tabstop=4 shiftwidth=4 fileencoding=utf-8 noexpandtab: */
#ifndef __smintf_h__
#define __smintf_h__
#include<stdarg.h>

char* smintf(const char *format, ...);
char* mintf(const char *format, ...);
void _print_integer(int, int, char*, int* , int, char*, int*);
int _s_mintf_helper(char*, va_list, int, const char*);
void _print_out(char);


// Bonus option only:
// void mintf(const char *format, ...);

#endif
