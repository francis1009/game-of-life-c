#ifndef GAME_H
#define GAME_H

#include "config.h"

typedef struct {
	unsigned char gfx[WINDOW_WIDTH * WINDOW_HEIGHT];
} Game;

void game_init(Game *game);
void game_next_frame(Game *game);	

#endif
