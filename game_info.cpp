#include "snake.hpp"
void GameInfo_t ::updateCurrentState() {
  wrefresh(field), wrefresh(info), wrefresh(menu);
  curs_set(0);
  if (data.speed == 0) {
    initialField(), run = over = 0;
  } else if (data.speed > 0) {
    gameRunning(), run = 1, over = 0;
    if (prev < 0) wclear(field), wrefresh(field), prev = 0;
  } else if (data.speed < -1)
    gameOver(), over = 1, run = 0, data.speed = -1, prev = -1;
  wattron(field, COLOR_PAIR(11)), box(field, 0, 0),
      wattroff(field, COLOR_PAIR(11));
  for (int y = 1; y < 21; y++)
    for (int x = 1; x < 11; x++)
      wattron(field, COLOR_PAIR(0)), mvwprintw(field, y, x, " "),
          wattroff(field, COLOR_PAIR(0));
  if (data.speed) {
    wattron(field, COLOR_PAIR(3)),
        mvwprintw(field, data.snake[0].y, data.snake[0].x, "\u25cf"),
        wattroff(field, COLOR_PAIR(3));
    for (int i = 1; data.snake[i].n; i++)
      wattron(field, COLOR_PAIR(2)),
          mvwprintw(field, data.snake[i].y, data.snake[i].x, "\u25cf"),
          wattroff(field, COLOR_PAIR(2));
    wattron(field, COLOR_PAIR(1)),
        mvwprintw(field, data.appleY, data.appleX, "\u25cf"),
        wattroff(field, COLOR_PAIR(1));
  }
}
