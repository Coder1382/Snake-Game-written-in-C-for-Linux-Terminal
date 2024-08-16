#include "../../brick_game/snake/s21_snake.hpp"
using namespace s21;
void GameInfo_t ::initialField() {
  wattron(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10)),
      mvwprintw(info, 2, 1, "Score %d     ", data.score),
      mvwprintw(info, 3, 1, "Level %d ", data.level),
      mvwprintw(info, 8, 0, "READY TO START"),
      mvwprintw(menu, 4, 1, "Start - Enter"),
      mvwprintw(menu, 5, 1, "Quit - Esc"), wattroff(info, COLOR_PAIR(10)),
      wattroff(menu, COLOR_PAIR(10)), wattron(field, COLOR_PAIR(11)),
      box(field, 0, 0), wattroff(field, COLOR_PAIR(11));
}
void GameInfo_t ::setColors() {
  start_color(), init_color(1, 600, 0, 0), init_color(2, 0, 900, 0),
      init_color(3, 943, 720, 0), init_color(0, 175, 225, 225),
      init_color(10, 1000, 1000, 1000), init_color(11, 170, 170, 170),
      init_pair(1, 1, 0), init_pair(2, 2, 0), init_pair(3, 3, 0),
      init_pair(0, 0, 0), init_pair(10, 10, 0), init_pair(11, 11, 11),
      init_pair(12, 11, 0);
}
void GameInfo_t ::gameOver() {
  if (over == 0) {
    wclear(menu), wattron(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10)),
        mvwprintw(info, 8, 0, "GAME OVER       "),
        mvwprintw(info, 1, 1, "Score %d     ", data.score),
        mvwprintw(info, 2, 1, "Record %d     ",
                  data.score > data.high_score ? data.score : data.high_score),
        mvwprintw(info, 3, 1, "Level %d ", data.level),
        mvwprintw(menu, 5, 1, "Restart - Enter"),
        mvwprintw(menu, 6, 1, "Quit - Esc");
  }
  wattroff(info, COLOR_PAIR(10)), wattroff(menu, COLOR_PAIR(10));
}
void GameInfo_t ::gameRunning() {
  wattron(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10));
  mvwprintw(info, 1, 1, "Score %d     ", data.score),
      mvwprintw(info, 2, 1, "Record %d     ",
                data.score > data.high_score ? data.score : data.high_score),
      mvwprintw(info, 3, 1, "Level %d ", data.level),
      mvwprintw(info, 4, 1, "Speed %.1fs  ", data.speed / 10.0);
  if (data.pause && cease == 0)
    wclear(menu), cease = 1, mvwprintw(info, 8, 0, "GAME ON PAUSE   "),
                  mvwprintw(menu, 4, 1, "Resume - Space\n"),
                  mvwprintw(menu, 5, 1, "Quit - Esc\n"), cease = 1;
  else if (data.pause == 0 && (cease || run == 0)) {
    cease ? cease = 0 : 0;
    wclear(menu), mvwprintw(info, 8, 0, "GAME IN PROGRESS"),
        mvwprintw(menu, 0, 5, "MENU"),
        mvwprintw(menu, 1, 1, "Left - LeftArrow"),
        mvwprintw(menu, 2, 1, "Right - RightArrow"),
        mvwprintw(menu, 3, 1, "Down - DownArrow"),
        mvwprintw(menu, 4, 1, "Up - UpArrow"),
        mvwprintw(menu, 5, 1, "Fast - hold Tab"),
        mvwprintw(menu, 6, 1, "Pause - Space"),
        mvwprintw(menu, 7, 1, "Quit - Esc");
  }
  wattroff(info, COLOR_PAIR(10)), wattron(menu, COLOR_PAIR(10));
}