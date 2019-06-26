#include <math.h>
#include <stdlib.h>
#include "game.h"

int _rand_num(int max) {
  return (int) round(rand() * max);
}

void _setup_game(struct ms_game *game, int rows, int cols, int mines) {
  /* Set rows and cols */
  game->rows = rows;
  game->cols = cols;
  game->mines = mines;

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

void init_game(struct ms_game *game) {
  game->map = NULL;
  game->rows = 0;
  game->cols = 0;
  game->mines = 0;
  game->cursor_row = 0;
  game->cursor_col = 0;
}

void generate_map(struct ms_game *game, int row, int col) {

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

void delete_game(struct ms_game *game) {
  for (int i = 0; i < game->rows; i++)
    free(game->map[i]);
  free(game->map);
}

