#include <curses.h>
#include <stdlib.h>
#include "input.h"
#include "game.h"
#include "graphics.h"

#define STR_BUFFER_SIZE 20

int ask_difficulty(int *rows, int *cols, int *mines) {
  /* Start game and ask for difficulty */
  clear();
  int selection;
  printw("Please select a difficulty\n1 Easy\n2 Intermediate\n3 Expect\n4 Custom\n");
  do {
    selection = getch();
  } while (selection > '4' || selection < '1');

  /* Parse selection */
  selection -= '0';
  if (selection == 4) {
    clear();
    echo();
    nocbreak();

    // Get rows
    printw("Rows: ");
    char rows_str[STR_BUFFER_SIZE];
    getstr(rows_str);
    *rows = atoi(rows_str);
    
    // Get cols
    printw("Cols: ");
    char cols_str[STR_BUFFER_SIZE];
    getstr(cols_str);
    *cols = atoi(cols_str);
    
    // Get mines
    printw("Mines: ");
    char mines_str[STR_BUFFER_SIZE];
    getstr(mines_str);
    *mines = atoi(mines_str);

    noecho();
    cbreak();
  }
  return selection;
}

int main() {
  /* Initialize curses */
  init_input();

  /* Initialize game */
  struct ms_game game;
  init_game(&game);
  
  int rows;
  int cols;
  int mines;
  int selection = ask_difficulty(&rows, &cols, &mines);

  if (selection == -1)
    return -1;
  /* Setup the game and then draw it on the screen */
  setup_game(&game, selection, rows, cols, mines);
  clear();
  gfx_draw_game(&game);
  refresh();

  /* Main game loop */
  while (true) {
    int key = getch();
    switch (key) {
      // For each direction key, check if cursor is at an edge, if it is don't allow it to
      // overflow / wrap
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
        break;
      // Discover a cell
      case ' ':
        // If the map has not been generated, generate it
        if (!game.map_generated)
          generate_map(&game);
        check_cell(&game);
        break;
      case 'f':
      case 'F':
        // Flag or unflag cell at current cursor pos
        flag_cell(&game);
        break;
      case 'd':
      case 'D':
        // Change difficulty
        selection = ask_difficulty(&rows, &cols, &mines);
        // Don't break so we restart the game
      case 'r':
      case 'R':
        // Restart game
        setup_game(&game, selection, rows, cols, mines);
        generate_map(&game);
        break;
    }

    clear(); 
    // If game is over, display win message
    if (game.cells_left == 0)
      printw("You won!\n");
    gfx_draw_game(&game);
    refresh();
  }

  deinit_input();
  delete_game(&game);
  return 0;
}

