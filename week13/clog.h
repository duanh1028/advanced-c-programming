#include<stdbool.h>
#include<stdio.h>
#include<unistd.h>
#ifndef __CLOG_H__
#define __CLOG_H__

	const char* ANSI_RED       = "\x1b[31m";
	const char* ANSI_GREEN     = "\x1b[32m";
	const char* ANSI_YELLOW    = "\x1b[33m";
	const char* ANSI_BLUE      = "\x1b[34m";
	const char* ANSI_MAGENTA   = "\x1b[35m";
	const char* ANSI_CYAN      = "\x1b[36m";
	const char* ANSI_RESET     = "\x1b[0m";
	
#define log_int(n) fprintf(stderr, "%s == %d\n", (#n), (n))
#define log_msg(msg) fprintf(stderr, "%s", msg);
#define log_str(s) fprintf(stderr, "%s == %s\n", s, s)
#define log_char(ch) fprintf(stderr, "ch == '%c'\n", ch)
#define log_addr(addr) fprintf(stderr, "addr == %p\n", addr)

#ifdef DEBUG
#	define log_red(...) {\
		fprintf(stderr, ANSI_RED)\
		fprintf(stderr, __VA_ARGS__)\
		fprintf(stderr, ANSI_RESET)\
		fprintf(stderr, "\n")\
	}
#	define log_green(...) {\
		fprintf(stderr, ANSI_GREEN)\
		fprintf(stderr, __VA_ARGS__)\
		fprintf(stderr, ANSI_RESET)\
		fprintf(stderr, "\n");\
	}
#	define log_yellow(...) {\
		fprintf(stderr, ANSI_YELLOW)\
		fprintf(stderr, __VA_ARGS__)\
		fprintf(stderr, ANSI_RESET)\
		fprintf(stderr, "\n");\
	}	
#	define log_blue(...) {\
		fprintf(stderr, ANSI_BLUE)\
		fprintf(stderr, __VA_ARGS__)\
		fprintf(stderr, ANSI_RESET)\
		fprintf(stderr, "\n")\
	}
#	define log_magenta(...) {\
		fprintf(stderr, ANSI_MAGENTA);\
		fprintf(stderr, __VA_ARGS__);\
		fprintf(stderr, ANSI_RESET);\
		fprintf(stderr, "\n");\
	}
#	define log_cyan(...) {\
		fprintf(stderr, ANSI_CYAN)\
		fprintf(stderr, __VA_ARGS__)\
		fprintf(stderr, ANSI_RESET)\
		fprintf(stderr, "\n");\
	}
#else
#	define log_red
#	define log_green
#	define log_yellow
#	define log_blue
#	define log_magenta
#	define log_cyan
#endif

#endif


