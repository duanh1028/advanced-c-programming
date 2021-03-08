# VARIABLES
EXECUTABLE     = test_mintf
SRC_C          = mintf.c
SRC_H          = mintf.h clog.h miniunit.h
TEST_C         = test_mintf.c
TEST_EXPECTED  = test_mintf.txt
TEST_ACTUAL    = actual.txt
ASG_NICKNAME   = HW04
CFLAGS_GCOV    = $(CFLAG) -fprofile-arcs -ftest-coverage
CC             = gcc
CFLAGS         = -g -std=c99 -Wall -Wshadow -Wvla -Werror -pendantic

#RULES

test_mintf: mintf.c mintf.h clog.h
	gcc -o test_mintf mintf.c test_mintf.c -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic

coverage: 
	gcc -o test_mintf mintf.c test_mintf.c -fprofile-arcs -ftest-coverage -DNDEBUG;\
	./test_mintf;\
	gcov -f mintf.c

test: $(EXECUTABLE)
	./test_mintf > actual.txt;                                                   \
	diff -b actual.txt test_mintf.txt &> /dev/null;                                              \
	if [ $$? -eq 0 ]; then                                                       \
		./echo_color green "Test passed: actual.txt matches test_mintf.txt";      \
	else                                                                         \
		./echo_color red "Test failed: actual.txt does NOT match test_mintf.txt"; \
	fi

debug: 	
	gcc -o test_mintf mintf.c test_mintf.c -g -std=c99 -Wall -Wshadow -Wvla -Werror -pedantic -DDEBUG;

echo_color: 
	gcc -o echo_color echo_color.c miniunit.h clog.h 

submit: 
	264submit HW04 mintf.c test_mintf.c test_mintf.txt miniunit.h clog.h

pretest: 
	264test hw05

clean:
	rm -f test_mintf actual.txt test_mintf.txt echo_color
# .PHONY TARGET
.PHONY: submit pretest clean
