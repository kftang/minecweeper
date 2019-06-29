#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"

int _count_adj_mines(struct ms_game *game, int row, int col) {
  int max_rows = game->rows;
  int max_cols = game->cols;

  // Get bounds for row and col
  int row_min = row == 0 ? 0 : -1;
  int col_min = col == 0 ? 0 : -1;
  int row_max = row == max_rows - 1 ? 0 : 1;
  int col_max = col == max_cols - 1 ? 0 : 1;

  // Check adj cells for mines
  int adj_mines = 0;
  for (int i = row_min; i <= row_max; i++) {
    for (int j = col_min; j <= col_max; j++) {
      if ((game->map[row + i][col + j] & NUM_MASK) == MINE) {
        adj_mines++;
      }
    }
  }
  return adj_mines;
}

void _discover_around(struct ms_game *game, int row, int col) {
  ms_cell_t **map = game->map;
  ms_cell_t cell = map[row][col];
  
  // Set cell to be visible
  map[row][col] &= ~HIDDEN;
  map[row][col] |= SHOWN;

  // Decrement cells left
  game->cells_left--;
  
  // Check if we need to discover adj cells
  if ((cell & NUM_MASK) == 0 && (cell & HIDDEN)) {
    
    int max_rows = game->rows;
    int max_cols = game->cols;

    // Get bounds for row and col
    int row_min = row == 0 ? 0 : -1;
    int col_min = col == 0 ? 0 : -1;
    int row_max = row == max_rows - 1 ? 0 : 1;
    int col_max = col == max_cols - 1 ? 0 : 1;

    // Discover adj cells 
    for (int i = row_min; i <= row_max; i++) {
      for (int j = col_min; j <= col_max; j++) {
        _discover_around(game, row + i, col + j);
      }
    }
  }
}

void _setup_game(struct ms_game *game, int rows, int cols, int mines) {
  /* Set rows and cols */
  game->rows = rows;
  game->cols = cols;
  game->mines = mines;

  /* Cells left is used to determine if the game is won */
  game->cells_left = rows * cols - mines;

  /* Allocate map */
  game->map = malloc(sizeof(ms_cell_t *) * rows);
  for (int i = 0; i < rows; i++)
    game->map[i] = malloc(sizeof(ms_cell_t) * cols);

  /* Populate map with only hidden*/
  int mines_left = mines;
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      game->map[i][j] |= HIDDEN;
    }
  }
}

int _rand_num(int max) {
  return rand() % max;
}

void check_cell(struct ms_game *game) {
  int row = game->cursor_row;
  int col = game->cursor_col;
  ms_cell_t cell = game->map[row][col];

  // Only do something if the cell is hidden
  if (cell & HIDDEN) {
    // Lose condition
    if ((cell & NUM_MASK) == MINE) {
    // Discover cells 
    } else if ((cell & NUM_MASK) == 0) {
      _discover_around(game, row, col);
    // Show single cell
    } else {
      game->map[row][col] &= ~HIDDEN;
      game->map[row][col] |= SHOWN;
      game->cells_left--;
    }
  }
}

void delete_game(struct ms_game *game) {
  for (int i = 0; i < game->rows; i++)
    free(game->map[i]);
  free(game->map);
}

void flag_cell(struct ms_game *game) {
  int row = game->cursor_row;
  int col = game->cursor_col;
  ms_cell_t cell = game->map[row][col];
  
  // Only allow flag if the cell is still hidden
  if (cell & HIDDEN) {
    game->map[row][col] |= FLAG;
  }
}

void generate_map(struct ms_game *game) {
  int row = game->cursor_row;
  int col = game->cursor_col;
  int max_rows = game->rows;
  int max_cols = game->cols;
  int mines_left = game->mines;
  ms_cell_t **map = game->map;

  // Place mines around the field
  while (mines_left > 0) {
    int rand_row = _rand_num(max_rows);
    int rand_col = _rand_num(max_cols);
    // Make sure the random cell is not in a 1 radius around the starting cell
    if (abs(rand_row - row) < 2 && abs(rand_col - col) < 2) {
      continue;
    // Make sure the random cell is not already a mine
    } else if ((map[rand_row][rand_col] & NUM_MASK) == MINE) {
      continue;
    // Set the cell as a mine
    } else {
      map[rand_row][rand_col] |= MINE;
      mines_left--;
    }
  }
  
  // Generate numbers for all cells now
  for (int i = 0; i < max_rows; i++) {
    for (int j = 0; j < max_cols; j++) {
      // Skip mines
      if ((map[i][j] & NUM_MASK) == MINE)
        continue;

      // Get number of adj mines and set it to the cell
      int adj_mines = _count_adj_mines(game, i, j);
      map[i][j] |= (uint16_t) adj_mines;
    }
  }

  // Set map as generated
  game->map_generated = true;
}

void init_game(struct ms_game *game) {
  game->map = NULL;
  game->map_generated = false;
  game->rows = 0;
  game->cols = 0;
  game->mines = 0;
  game->cells_left = 0;
  game->cursor_row = 0;
  game->cursor_col = 0;
  srand(time(0));
}

void setup_game(struct ms_game *game, int difficulty) {
  switch (difficulty) {
    default:
    case 1: 
      _setup_game(game, 9, 9, 10);
      break;
    case 2:
      _setup_game(game, 16, 16, 40);
      break;
    case 3:
      _setup_game(game, 16, 30, 99);
      break;
  }
}

