#ifndef SNAKE_H
#define SNAKE_H
#include <fcntl.h>
#include <gtest/gtest.h>
#include <locale.h>
#include <ncurses.h>
#include <time.h>
#include <uchar.h>
#include <unistd.h>
#include <wchar.h>
#include <iostream>
class Play {
 private:
  struct Snake {
    int n;
    int x;
    int y;
  };

 public:
  enum UserAction_t {
    Start = 10,
    Pause = 32,
    Terminate = 27,
    Action = 9,
    Left = KEY_LEFT,
    Right = KEY_RIGHT,
    Down = KEY_DOWN,
    Up = KEY_UP
  };
  bool horiz, vert;
  int field[22][12], score, high_score, level, pause, speed;
  int appleX, appleY, length;
  Snake snake[200];
};
class GameInfo_t {
 public:
  Play data;
  int count, run, over, prev, cease, input;
  wchar_t key;
  WINDOW *field, *info, *menu;
  double stop, trip;
  FILE *f;
  void starting();
  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();
  void shiftAhead();
  void eating();
  void setColors();
  void gameOver();
  void initialField();
  void gameRunning();
  void userInput(int);
  void updateCurrentState();
  GameInfo_t() {
    key = '\0';
    count = run = over = prev = cease = data.score = data.high_score =
        data.level = data.pause = data.length = 0;
    data.speed = stop = trip = 0;
    f = nullptr;
    setlocale(LC_ALL, "");
    initscr(), keypad(stdscr, true), cbreak(), noecho(), setColors(),
        nodelay(stdscr, true),
        count = 1, srand(time(NULL)), field = newwin(22, 12, 0, 25),
        info = newwin(11, 25, 0, 39), menu = newwin(9, 25, 12, 39);
  }
};
#endif
