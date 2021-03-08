#include<stdlib.h>
#include<stdio.h>
typedef struct {
	char den;
	int doo;
} Dog;

typedef struct {
	int ear;
	double elf;
	char* eye;
} Eel;

int main() {
	Dog dan = {
		.den = 'Y',
		.doo = 160
	};
	Dog* a_dan = &dan;
	Eel ela = {
		.ear = 162,
		.elf = 1.6,
		.eye = "egg"
	};
	Eel* a_ela = &ela;
	int xia[5] = {0x68, 0x4b, 0x10, 0x59, 0x30};
	printf("The first number of xia is %d", xia[0]);
	printf("\na_dan is %dand a_ela %d", a_dan -> doo, a_ela -> ear);

	return EXIT_SUCCESS;
}

