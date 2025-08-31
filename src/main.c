#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL3/SDL.h>

#include "config.h"
#include "display.h"
#include "input.h"

const int TARGET_FPS = 60;
const float FRAME_DURATION_MS = 1000.0f / TARGET_FPS;
const int CYCLES_PER_FRAME = 1000;

int main(void) {
	srand(time(NULL));

	bool is_running = display_init();
	if (!is_running) {
		fprintf(stderr, "Error: Failed to initialize display. Exiting.\n");
		SDL_Quit();
		return 1;
	}

	unsigned char gfx[WINDOW_WIDTH * WINDOW_HEIGHT];
	memset(gfx, 0, sizeof(gfx));

	while (is_running) {
		Uint64 frame_start_time = SDL_GetTicks();

		for (int i = 0; i < CYCLES_PER_FRAME; i++) {
			process_input(&is_running, gfx);
		}

		display_draw(gfx);

		Uint64 frame_end_time = SDL_GetTicks();
		float elapsed_ms = (float) (frame_end_time - frame_start_time);
		if (elapsed_ms < FRAME_DURATION_MS) {
			SDL_Delay((Uint32) (FRAME_DURATION_MS - elapsed_ms));
		}
	}

	display_destroy();
	SDL_Quit();
	return 0;
}
