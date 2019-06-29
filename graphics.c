#include <curses.h>
#include <stdlib.h>
#include "game.h"

void gfx_draw_game(struct ms_game *game) {
  printw("Game info\ncols: %d\nrows: %d\ncells left: %d\n", game->cols, game->rows, game->cells_left);
  // Display top border
  for (int i = 0; i < 3 * game->cols + 2; i++)
    printw("-");
  printw("\n");

  // Display cells and side border
  for (int i = 0; i < game->rows; i++) {
    printw("|");
    for (int j = 0; j < game->cols; j++) {
      // If the player has the current cell selected show an x
      if (i == game->cursor_row && j == game->cursor_col) {
        printw("[x]");
      // Otherwise show whatever the cell contains
      } else {
        ms_cell_t cell = game->map[i][j];
        if (CELL_IS_FLAGGED(cell)) {
          printw("[F]");
        } else if (CELL_IS_SHOWN(cell)) {
          printw("[%d]", CELL_NUMBER(cell));
        } else if (CELL_IS_HIDDEN(cell)) {
          printw("[ ]");
        }
      }
    }
    printw("|\n");
  }

  // Display bottom border
  for (int i = 0; i < 3 * game->cols + 2; i++)
    printw("-");
}

