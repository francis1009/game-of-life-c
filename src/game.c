#include "game.h"

#include <string.h>

#include "config.h"

static int count_live_neighbours(unsigned char gfx[], int r, int c) {
	int live_count = 0;
	for (int i = r - 1; i <= r + 1; i++) {
		for (int j = c - 1; j <= c + 1; j++) {
			if (i == r && j == c) {
				continue;
			}

			if (i < 0 || j < 0 || i >= WINDOW_HEIGHT || j >= WINDOW_WIDTH) {
				continue;
			}

			int neighbor_index = i * WINDOW_WIDTH + j;
			if (gfx[neighbor_index] == 1 || gfx[neighbor_index] == 3) {
				live_count++;
			}
		}
	}
	return live_count;
}

void game_init(Game *game) {
	memset(game->gfx, 0, sizeof(game->gfx));
}

void game_next_frame(Game *game) {
	for (int r = 0; r < WINDOW_HEIGHT; r++) {
		for (int c = 0; c < WINDOW_WIDTH; c++) {
			int idx = r * WINDOW_WIDTH + c;
			int live_neighbours = count_live_neighbours(game->gfx, r, c);
			if (game->gfx[idx] == 1 &&
					(live_neighbours == 2 || live_neighbours == 3)) {
				game->gfx[idx] = 3;
			} else if (game->gfx[idx] == 0 && live_neighbours == 3) {
				game->gfx[idx] = 2;
			}
		}
	}

	for (int i = 0; i < WINDOW_WIDTH * WINDOW_HEIGHT; i++) {
		if (game->gfx[i] == 1) {
			game->gfx[i] = 0;
		} else if (game->gfx[i] == 2 || game->gfx[i] == 3) {
			game->gfx[i] = 1;
		}
	}
}
