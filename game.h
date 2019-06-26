#ifndef GAME__H
#define GAME__H

#include <stdbool.h>
#include <stdint.h>

/* Cell Types */
#define HIDDEN  0x1000
#define SHOWN   0x0100
#define FLAG    0x0010
#define ONE     0x0001
#define TWO     0x0002
#define THREE   0x0003
#define FOUR    0x0004
#define FIVE    0x0005
#define SIX     0x0006
#define SEVEN   0x0007
#define EIGHT   0x0008
#define ZERO    0x0000
#define MINE    0x000F

#define NUM_MASK 0x000F

typedef uint16_t ms_cell_t;

struct ms_game {
  ms_cell_t **map;
  bool      map_generated;
  uint8_t   rows;
  uint8_t   cols;
  uint8_t   mines;
  uint8_t   cursor_row;
  uint8_t   cursor_col;
};

void init_game(struct ms_game *game);

void setup_game(struct ms_game *game, int difficulty);

void generate_map(struct ms_game *game);

void delete_game(struct ms_game *game);
#endif

