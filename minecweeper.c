#include <curses.h>
#include "input.h"
#include "game.h"
#include "graphics.h"

int main() {
  /* Initialize curses */
  init_input();

  /* Initialize game */
  struct ms_game game;
  init_game(&game);

  /* Start game and ask for difficulty */

  int selection;
  printw("Please select a difficulty\n1 Easy\n2 Intermediate\n3 Expect\n4 Custom\n");
  do {
    selection = getch();
  } while (selection > '4' || selection < '1');

  /* Parse selection */
  selection -= '1';
  if (selection == 4) {
    deinit_input();
    return -1;
  }
  setup_game(&game, selection);
  gfx_draw_game(&game);
  refresh();

  while (true) {
    int key = getch();
    switch (key) {
      case KEY_UP:
        game.cursor_row = game.cursor_row == 0 ? 0 : game.cursor_row - 1;
        break;
      case KEY_DOWN:
        game.cursor_row = game.cursor_row == game.rows - 1 ? game.rows - 1 : game.cursor_row + 1;
        break;
      case KEY_LEFT:
        game.cursor_col = game.cursor_col == 0 ? 0 : game.cursor_col - 1;
        break;
      case KEY_RIGHT:
        game.cursor_col = game.cursor_col == game.cols - 1 ? game.cols - 1 : game.cursor_col + 1;
    }
    gfx_draw_game(&game);
    refresh();
  }

  deinit_input();
  return 0;
}

