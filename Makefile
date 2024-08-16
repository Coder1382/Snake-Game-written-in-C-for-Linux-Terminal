#.PHONY: all clean dist dvi install uninstall
RUN = gcc -Wall -Werror -Wextra -O2 -std=c11 --pedantic
ifeq ($(shell uname),Linux)
	OS = -lcheck -lm -lrt -lpthread -lsubunit -lncursesw -lgcov
else
	OS = -lcheck -lm -lpthread -lncursesw -lgcov
endif
all:	clean snake.a test gcov_report
s21_snake.a:	snake.o
	ar rcs snake.a *.o
	ranlib snake.a
s21_snake.o:	snake/*.c gui/cli/*.c *.h
	$(RUN) *.c *.c -c
clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a tests/*.gcno *.tar.gz tests/report test.dSYM docs/html docs/latex report
s21_snake_install.o:	*.c *.h
snake:	s21_snake_install.o
	$(RUN) *.c -o snake $(OS)
install:	snake
	mkdir snake_game
	install snake snake_game
play:
	./snake
uninstall:
	rm -rf snake_game
