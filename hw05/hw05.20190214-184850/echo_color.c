#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"clog.h"
#include"miniunit.h"

int main(int argc, char* argv[]) {
	if(argc == 3) {
		if(!strcmp(argv[1], "red")) {
			fprintf(stderr, ANSI_RED);
			fprintf(stderr, argv[2]);
			fprintf(stderr, ANSI_RESET);
			fprintf(stderr, "\n");
		}
		else if(!strcmp(argv[1], "green")) {
			fprintf(stderr, ANSI_GREEN);
			fprintf(stderr, argv[2]);
			fprintf(stderr, ANSI_RESET);
			fprintf(stderr, "\n");
		}
		else if(!strcmp(argv[1], "yellow")) {
			fprintf(stderr, ANSI_YELLOW);
			fprintf(stderr, argv[2]);
			fprintf(stderr, ANSI_RESET);
			fprintf(stderr, "\n");
		}
		else if(!strcmp(argv[1], "blue")) {
			fprintf(stderr, ANSI_BLUE);
			fprintf(stderr, argv[2]);
			fprintf(stderr, ANSI_RESET);
			fprintf(stderr, "\n");
		}
		else if(!strcmp(argv[1], "magenta")) {
			fprintf(stderr, ANSI_MAGENTA);
			fprintf(stderr, argv[2]);
			fprintf(stderr, ANSI_RESET);
			fprintf(stderr, "\n");
		}
		else if(!strcmp(argv[1], "cyan")) {
			fprintf(stderr, ANSI_CYAN);
			fprintf(stderr, argv[2]);
			fprintf(stderr, ANSI_RESET);
			fprintf(stderr, "\n");
			
		}
		else {
			fprintf(stderr, "Usage:  %s <\"red\"|\"green\"|\"yellow\"|\"blue\"|\"magenta\"|\"cyan\"> STRING", argv[1]);
			return EXIT_FAILURE;
		}
	}
	else{
		fprintf(stderr, "Usage:  %s <\"red\"|\"green\"|\"yellow\"|\"blue\"|\"magenta\"|\"cyan\"> STRING", argv[1]);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;

}
