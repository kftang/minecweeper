#include <curses.h>
#include <stdlib.h>
#include "game.h"
#include "graphics.h"

void gfx_init() {
  start_color();

  init_pair(MSCOLOR_HIDDEN, COLOR_WHITE, COLOR_BLACK);
  init_pair(MSCOLOR_MINE, COLOR_WHITE, COLOR_RED);
  init_pair(MSCOLOR_FLAG, COLOR_WHITE, COLOR_RED);
  init_pair(MSCOLOR_CURSOR, COLOR_BLACK, COLOR_YELLOW);
  init_pair(MSCOLOR_DEFAULT, COLOR_WHITE, COLOR_BLACK);
}

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
      ms_cell_t cell = game->map[i][j];
      bool cell_selected = i == game->cursor_row && j == game->cursor_col;
      if (CELL_IS_FLAGGED(cell)) {
      
        // Use red text for flags
        attron(cell_selected ? COLOR_PAIR(MSCOLOR_CURSOR) : COLOR_PAIR(MSCOLOR_FLAG));
        printw("[F]");
      } else if (CELL_IS_MINE(cell) && CELL_IS_SHOWN(cell)) {

        // Use red background for mines
        attron(cell_selected ? COLOR_PAIR(MSCOLOR_CURSOR) : COLOR_PAIR(MSCOLOR_MINE));

        // If cell is a mine, display * instead of 15, used for when you lose
        printw("[*]");
      } else if (CELL_IS_SHOWN(cell)) {
        
        attron(cell_selected ? COLOR_PAIR(MSCOLOR_CURSOR) : COLOR_PAIR(MSCOLOR_DEFAULT));
        printw("[%d]", CELL_NUMBER(cell));
      } else if (CELL_IS_HIDDEN(cell)) {

        // Use white background for hidden cells
        attron(cell_selected ? COLOR_PAIR(MSCOLOR_CURSOR) : COLOR_PAIR(MSCOLOR_HIDDEN));
        printw("[ ]");
      }

      // Switch to default color
      attron(COLOR_PAIR(MSCOLOR_DEFAULT));
    }
    printw("|\n");
  }

  // Display bottom border
  for (int i = 0; i < 3 * cols + 2; i++)
    printw("-");
  printw("\n");
}

