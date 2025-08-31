#include "game.h"

#include <string.h>

void game_init(Game *game) {
	memset(game->gfx, 0, sizeof(game->gfx));
}

void game_next_frame(Game *game) {
}
