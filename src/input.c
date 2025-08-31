#include "input.h"

#include <SDL3/SDL.h>

#include "config.h"
#include "game.h"

static bool is_mouse_down = false;

static void draw_pixel_at(unsigned char gfx[], int x, int y) {
	// Check if the coordinates are within the window bounds
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
		gfx[y * WINDOW_WIDTH + x] = 1;
	}
}

void input_process(const Game *game, bool *is_running) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		// Handle closing window
		case SDL_EVENT_QUIT:
			*is_running = false;
			return;

		case SDL_EVENT_KEY_DOWN:
			// Quit program if 'Esc' key is pressed
			if (event.key.scancode == SDL_SCANCODE_ESCAPE) {
				*is_running = false;
				return;
			}
			break;

		// Draw if mouse down
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				is_mouse_down = true;
				int sim_x = event.button.x / WINDOW_SCALE;
				int sim_y = event.button.y / WINDOW_SCALE;
				draw_pixel_at(game->gfx, sim_x, sim_y);
			}
			break;

		// Prevent draw on mouse up
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				is_mouse_down = false;
			}
			break;

		// Continue draw if mouse down
		case SDL_EVENT_MOUSE_MOTION:
			if (is_mouse_down) {
				int sim_x = event.motion.x / WINDOW_SCALE;
				int sim_y = event.motion.y / WINDOW_SCALE;
				draw_pixel_at(game->gfx, sim_x, sim_y);
			}
			break;
		}
	}
}
