SRCS = calc.c parsing.c stack.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE -lm
GTKFlagOpen = `pkg-config --cflags gtk4`
GTKFlagClose = `pkg-config --libs gtk4` 

PACKAGE = smart_calc
VERSION = `date +"%Y.%m.%d"`
ARCHIVE = $(PACKAGE)-$(VERSION)

all: clean smart_calculator checks tests


smart_calculator: ${SRCS}
	${CC} ${CFLAGS} ${GTKFlagOpen} -o smart_calculator ${SRCS} calculator.c ${GTKFlagClose} 


tests:
	${CC} ${CFLAGS} tests.c ${SRCS} -lcheck -o tests
	./tests

gcov_report:
	@gcc --coverage tests.c -lcheck ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a *.out *.tar tests smart_calculator unit-test *.gcno *gcda report *.info main

checks: cppcheck style leaks

style:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c

leaks: tests
	CK_FORK=no leaks --atExit -- ./tests
	

install: smart_calculator
	@mkdir ~/SmartCalc_v1.0
	@install ./smart_calculator ~/SmartCalc_v1.0
uninstall:
	@rm -Rf ~/SmartCalc_v1.0
dvi:
	open readme.html
dist:
	@tar -cf $(ARCHIVE).tar *.c *.h Makefile