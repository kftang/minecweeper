#ifndef GRAPHICS__H
#define GRAPHICS__H

#include "game.h"

#define MSCOLOR_HIDDEN 1
#define MSCOLOR_MINE 2
#define MSCOLOR_FLAG 3
#define MSCOLOR_CURSOR 4
#define MSCOLOR_DEFAULT 5

void gfx_init();

void gfx_draw_game(struct ms_game *game);

#endif
