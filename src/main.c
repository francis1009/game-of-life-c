#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <SDL3/SDL.h>

#include "config.h"
#include "display.h"
#include "game.h"
#include "input.h"

const int TARGET_FPS = 500;
const float FRAME_DURATION_MS = 1000.0f / TARGET_FPS;

int main(void) {
	srand(time(NULL));

	bool is_running = display_init();
	if (!is_running) {
		fprintf(stderr, "Error: Failed to initialize display. Exiting.\n");
		SDL_Quit();
		return 1;
	}

	Game game;
	game_init(&game);
	bool is_paused = false;

	while (is_running) {
		Uint64 frame_start_time = SDL_GetTicks();
		input_process(&game, &is_running, &is_paused);
		display_draw(&game);

		if (!is_paused) {
			game_next_frame(&game);
		}

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
