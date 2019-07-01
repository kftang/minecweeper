#include <curses.h>
#include <stdlib.h>
#include "game.h"

void gfx_draw_game(struct ms_game *game) {
  int rows = game->rows;
  int cols = game->cols;
  int cells_left = game->cells_left;
  // Only display game info if game is not over
  if (game->cells_left > 0)
    printw("Game Info\nCells Left: %d\n\n", cells_left);
  printw("Controls\nSpace: Discover Cell\nF: Flag Cell\nR: Restart Game\nD: Change Difficulty\n");
  // Display top border
  for (int i = 0; i < 3 * game->cols + 2; i++)
    printw("-");
  printw("\n");

  // Display cells and side border
  for (int i = 0; i < rows; i++) {
    printw("|");
    for (int j = 0; j < cols; j++) {
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
  for (int i = 0; i < 3 * cols + 2; i++)
    printw("-");
  printw("\n");
}

