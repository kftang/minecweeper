#include <curses.h>
#include <stdlib.h>
#include "game.h"

void gfx_draw_game(struct ms_game *game) {
  clear();
  printw("Game info\ncols: %d\nrows: %d\ngenned: %d\n", game->cols, game->rows, game->map_generated);
  // Display top border
  for (int i = 0; i < 3 * game->cols + 2; i++)
    printw("-");
  printw("\n");

  // Display cells and side border
  char *cell_str = malloc(sizeof(char) * 4);
  for (int i = 0; i < game->rows; i++) {
    printw("|");
    for (int j = 0; j < game->cols; j++) {
      // If the player has the current cell selected show an x
      if (i == game->cursor_row && j == game->cursor_col) {
        printw("[x]");
      // Otherwise show whatever the cell contains
      } else {
        ms_cell_t cell = game->map[i][j];
        if (cell & HIDDEN) {
          printw("[ ]");
        } else if (cell & SHOWN) {
          printw("[%d]", cell & NUM_MASK);
        } else if (cell & FLAG) {
          printw("[F]");
        }
      }
    }
    printw("|\n");
  }

  // Display bottom border
  for (int i = 0; i < 3 * game->cols + 2; i++)
    printw("-");
  free(cell_str);
}

