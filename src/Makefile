SRCS = s21_calc.c s21_parsing.c s21_stack.c
	
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_GNU_SOURCE -lm
GTKFlagOpen = `pkg-config --cflags gtk4`
GTKFlagClose = `pkg-config --libs gtk4` 

PACKAGE = s21_smart_calc
VERSION = `date +"%Y.%m.%d"`
ARCHIVE = $(PACKAGE)-$(VERSION)

all: clean s21_smart_calculator checks tests


s21_smart_calculator: ${SRCS}
	${CC} ${CFLAGS} ${GTKFlagOpen} -o s21_smart_calculator ${SRCS} s21_calculator.c ${GTKFlagClose} 


tests:
	${CC} ${CFLAGS} s21_tests.c ${SRCS} -lcheck -o tests
	./tests

gcov_report:
	@gcc --coverage s21_tests.c -lcheck ${SRCS} -o unit-test
	@./unit-test
	@lcov -t "test" -o test.info -c -d .
	@genhtml -o report test.info
	
clean:
	@/bin/rm -rf *.o *.a *.out *.tar tests s21_smart_calculator unit-test *.gcno *gcda report *.info main

checks: cppcheck style leaks

style:
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem . *.c

leaks: tests
	CK_FORK=no leaks --atExit -- ./tests
	

install: s21_smart_calculator
	@mkdir ~/SmartCalc_v1.0
	@install ./s21_smart_calculator ~/SmartCalc_v1.0
uninstall:
	@rm -Rf ~/SmartCalc_v1.0
dvi:
	open readme.html
dist:
	@tar -cf $(ARCHIVE).tar *.c *.h Makefile