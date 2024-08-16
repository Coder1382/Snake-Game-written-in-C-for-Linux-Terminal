#include "s21_snake.hpp"
using namespace s21;
void GameInfo_t ::starting() {
  for (int i = 0; i < 200;
       data.snake[i].n = data.snake[i].x = data.snake[i].y = 0, i += 1) {
  };
  data.score = 0, data.pause = 0, data.length = 4, data.level = 1,
  data.speed = 12, data.vert = 1, data.horiz = 0;
  stop = ((double)clock()) + CLOCKS_PER_SEC * data.speed / 10.0,
  trip = ((double)clock()) + CLOCKS_PER_SEC / 5;
  (f = fopen("max_score.txt", "r")) == NULL ||
          fscanf(f, "%d", &data.high_score) == -1
      ? data.high_score = 0
      : 0;
  f ? fclose(f) : 0;
  for (int i = 9; i < 13; i++) {
    data.snake[i - 9].n = i - 8, data.snake[i - 9].x = 5,
                   data.snake[i - 9].y = i;
  }
  for (int i = 1, j = 0; i; j = 0) {
    data.appleX = rand() % 10 + 1, data.appleY = rand() % 20 + 1;
    for (; j < 200 &&
           !(data.snake[j].y == data.appleY && data.snake[j].x == data.appleX);
         j += 1)
      ;
    if (j == 200) i = 0;
  }
  flushinp();
}
void GameInfo_t ::moveLeft() {
  int i = 1;
  for (; data.snake[i].n && !(data.snake[i].x == data.snake[0].x - 1 &&
                              data.snake[i].y == data.snake[0].y);
       i += 1)
    ;
  if (data.snake[i].n) {
    data.speed = -100;
    return;
  }
  if (data.snake[0].x == 1)
    data.speed = -100;
  else {
    if (!(data.appleY == data.snake[0].y &&
          data.appleX == data.snake[0].x - 1)) {
      for (i = 199; data.snake[i].n == 0; i -= 1)
        ;
      for (i -= 1; i >= 0; data.snake[i + 1].y = data.snake[i].y,
                                          data.snake[i + 1].x = data.snake[i].x,
                                          i -= 1)
        ;
      data.snake[0].x = data.snake[0].x - 1;
    } else
      eating();
  }
}
void GameInfo_t ::moveRight() {
  int i = 1;
  for (; data.snake[i].n && !(data.snake[i].x == data.snake[0].x + 1 &&
                              data.snake[i].y == data.snake[0].y);
       i += 1)
    ;
  if (data.snake[i].n) {
    data.speed = -100;
    return;
  }
  if (data.snake[0].x == 10)
    data.speed = -100;
  else {
    if (!(data.appleY == data.snake[0].y &&
          data.appleX == data.snake[0].x + 1)) {
      for (i = 199; data.snake[i].n == 0; i -= 1)
        ;
      for (i -= 1; i >= 0; data.snake[i + 1].y = data.snake[i].y,
                                          data.snake[i + 1].x = data.snake[i].x,
                                          i -= 1)
        ;
      data.snake[0].x = data.snake[0].x + 1;
    } else
      eating();
  }
}
void GameInfo_t ::moveDown() {
  int i = 1;
  for (; data.snake[i].n && !(data.snake[i].y == data.snake[0].y + 1 &&
                              data.snake[i].x == data.snake[0].x);
       i += 1)
    ;
  if (data.snake[i].n) {
    data.speed = -100;
    return;
  }
  if (data.snake[0].y == 20)
    data.speed = -100;
  else {
    if (!(data.appleY == data.snake[0].y + 1 &&
          data.appleX == data.snake[0].x)) {
      for (i = 199; data.snake[i].n == 0; i -= 1)
        ;
      for (i -= 1; i >= 0; data.snake[i + 1].y = data.snake[i].y,
                                          data.snake[i + 1].x = data.snake[i].x,
                                          i -= 1)
        ;
      data.snake[0].y = data.snake[0].y + 1;
    } else
      eating();
  }
}
void GameInfo_t ::moveUp() {
  int i = 1;
  for (; data.snake[i].n && !(data.snake[i].y == data.snake[0].y - 1 &&
                              data.snake[i].x == data.snake[0].x);
       i += 1)
    ;
  if (data.snake[i].n) {
    data.speed = -100;
    return;
  }
  if (data.snake[0].y == 1)
    data.speed = -100;
  else {
    if (!(data.appleY == data.snake[0].y - 1 &&
          data.appleX == data.snake[0].x)) {
      for (i = 199; data.snake[i].n == 0; i -= 1)
        ;
      for (i -= 1; i >= 0; data.snake[i + 1].y = data.snake[i].y,
                                          data.snake[i + 1].x = data.snake[i].x,
                                          i -= 1)
        ;
      data.snake[0].y = data.snake[0].y - 1;
    } else
      eating();
  }
}
void GameInfo_t ::shiftAhead() {
  if (data.snake[1].y == data.snake[0].y - 1)
    moveDown();
  else if (data.snake[1].y == data.snake[0].y + 1)
    moveUp();
  else if (data.snake[1].x == data.snake[0].x - 1)
    moveRight();
  else if (data.snake[1].x == data.snake[0].x + 1)
    moveLeft();
}
void GameInfo_t ::eating() {
  int i = 199;
  if (data.snake[198].n)
    data.speed = -200;
  else {
    data.score += 1;
    if (data.score && data.score % 5 == 0 && data.level < 10)
      data.level += 1, data.speed -= 0.1;
    for (; data.snake[i].n == 0; i -= 1)
      ;
    data.snake[i + 1].n = data.snake[i].n + 1;
    for (; i >= 0; data.snake[i + 1].y = data.snake[i].y,
                                  data.snake[i + 1].x = data.snake[i].x, i -= 1)
      ;
    data.snake[0].y = data.appleY, data.snake[0].x = data.appleX;
    for (int i = 1, j = 0; i; j = 0) {
      data.appleX = rand() % 10 + 1, data.appleY = rand() % 20 + 1;
      for (; j < 200 && !(data.snake[j].y == data.appleY &&
                          data.snake[j].x == data.appleX);
           j += 1)
        ;
      if (j == 200) i = 0;
    }
  }
}