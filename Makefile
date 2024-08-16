#.PHONY: all clean dist dvi install uninstall
RUN = g++ -Wall -Werror -Wextra -O2 --pedantic -std=c++17 -g
#RUN = gcc -Wall -Werror -Wextra -O2 -std=c11 --pedantic
ifeq ($(shell uname),Linux)
	OS = -lgtest -lm -lrt -lpthread -lsubunit -lncursesw -lgcov -lgmock
else
	OS = -lgtest -lm -lpthread -lncursesw -lgcov -lgmock
endif
all:	clean s21_snake.a test gcov_report
s21_snake.a:	s21_snake.o
	ar rcs s21_snake.a *.o
	ranlib s21_snake.a
s21_snake.o:	brick_game/snake/s21*.cpp gui/desktop/s21*.cpp brick_game/snake/s21*.hpp
	$(RUN) brick_game/snake/s21*.cpp gui/desktop/s21*.cpp -c
test:	clean
	$(RUN) --coverage brick_game/snake/s21*.cpp gui/desktop/s21*.cpp tests/s21*.cpp -o testresult $(OS)
	./testresult
gcov_report:	test
	lcov -t "snake_test" -o snake.info -c -d .
	lcov --remove snake.info /usr/include/* -o snake.info
	genhtml -o report snake.info
	open report/index.html
	rm -rf *.gcno *gcda *.gcov
clang:
	clang-format -style=Google -n brick_game/snake/*.cpp gui/desktop/*.cpp brick_game/snake/*.hpp tests/*.cpp
style:
	clang-format -style=Google -i brick_game/snake/*.cpp gui/desktop/*.cpp brick_game/snake/*.hpp tests/*.cpp
clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a tests/*.gcno *.tar.gz tests/report test.dSYM docs/html docs/latex report
valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose make snake
s21_snake_install.o:	brick_game/snake/*.cpp gui/desktop/*.cpp brick_game/snake/*.hpp
install:
	mkdir gaming
	install games/* gaming
	qmake -o Makefile gaming/Snake.pro
	make
	./Snake
play:
	if test -d gaming; then
		./Snake
	else
		install
		./Snake
	fi
uninstall:	clean
	rm -rf gaming Snake .qmake.* *.txt
snake:	s21_snake_install.o
	$(RUN) brick_game/snake/*.cpp gui/desktop/*.cpp -o snake $(OS)
bare_install:	snake
	install snake snaking
bare_uninstall:
	rm -rf snaking
dist:
	tar czvf snake.tar.gz --ignore-failed-read brick_game gui tests Makefile Doxyfile menu.md chart.jpg
dvi:
	@doxygen
	$(shell which firefox || which xdg-open || which open || which x-www-browser) docs/html/index.html