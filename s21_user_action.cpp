#include "s21_snake.hpp"
using namespace s21;
void GameInfo_t ::userInput(int x) {
  updateCurrentState();
  key = x;
  if (data.speed > 0 && key == data.Pause)
    data.pause ? (data.pause = 0) : (data.pause = 1);
  else if (data.speed > 0 && data.pause == 0) {
    if (key == data.Left && data.vert == true)
      moveLeft(), data.horiz = true, data.vert = false;
    else if (key == data.Right && data.vert == true)
      moveRight(), data.horiz = true, data.vert = false;
    else if (key == data.Down && data.horiz == true)
      moveDown(), data.horiz = false, data.vert = true;
    else if (key == data.Up && data.horiz == true)
      moveUp(), data.horiz = false, data.vert = true;
    else if ((key != data.Action && (double)clock() >= stop) ||
             (key == data.Action && (double)clock() >= trip))
      shiftAhead(),
          stop = ((double)clock()) + CLOCKS_PER_SEC * data.speed / 10.0,
          trip = ((double)clock()) + CLOCKS_PER_SEC / 5;
  } else if (data.speed <= 0 && key == data.Start)
    starting();
  if (data.speed > 0 && data.score >= data.high_score){
    (f = fopen("max_score.txt", "w")) ? fprintf(f, "%d", data.score), fclose(f) : 0;
    data.high_score=data.score;
  }
  if (key == data.Terminate) {
    if (data.score >= data.high_score)
      (f = fopen("max_score.txt", "w")) ? fprintf(f, "%d", data.score),
          fclose(f)                     : 0;
    endwin();
    return;
  }
  userInput(getch());
}