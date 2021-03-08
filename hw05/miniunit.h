#include "clog.h"
#include <stdbool.h>

#define mu_start() int __mu_line_number = 0
#define mu_check(condition) do{\
	if(condition == false && __mu_line_number != 0) {\
		__mu_line_number = __LINE__;\
	}\
}while(false)

#define mu_run(function) if(function() == 0) {\
	fprintf(stderr, ANSI_GREEN);\
	fprintf(stderr, "Test passed: %s", __FILE__);\
	fprintf(stderr, "\n");\
	fprintf(stderr, ANSI_RESET);\
}\
else{\
	fprintf(stderr, ANSI_RED);\
	fprintf(stderr, "Test failed: %s at line %d", #function, __LINE__);\
	fprintf(stderr, "\n");\
	fprintf(stderr, ANSI_RESET);\
}\

#define mu_end() return __mu_line_number 
