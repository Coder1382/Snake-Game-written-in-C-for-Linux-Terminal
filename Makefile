#.PHONY: all clean dist dvi install uninstall
RUN = g++ -Wall -Werror -Wextra -O2 --pedantic -std=c++17 -g
ifeq ($(shell uname),Linux)
	OS = -lgtest -lm -lrt -lpthread -lsubunit -lncursesw -lgcov -lgmock
else
	OS = -lgtest -lm -lpthread -lncursesw -lgcov -lgmock
endif
all:	clean snake.a test gcov_report
s21_snake.a:	snake.o
	ar rcs snake.a *.o
	ranlib snake.a
s21_snake.o:	*.cpp *.hpp
	$(RUN) *.cpp -c
clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a tests/*.gcno *.tar.gz tests/report test.dSYM docs/html docs/latex report
s21_snake_install.o:	*.cpp *.hpp
snake:	s21_snake_install.o
	$(RUN) *.cpp -o snake $(OS)
install:	snake
	mkdir snake_game
	install snake snake_game
play:
	./snake
uninstall:
	rm -rf snake_game
