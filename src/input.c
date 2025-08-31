#include "input.h"

#include <SDL3/SDL.h>

#include "config.h"
#include "game.h"

static bool is_left_mouse_down = false;
static bool is_right_mouse_down = false;

static void draw_pixel_at(unsigned char gfx[], int x, int y, int pixel) {
	// Check if the coordinates are within the window bounds
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGHT) {
		gfx[y * WINDOW_WIDTH + x] = pixel;
	}
}

void input_process(Game *game, bool *is_running, bool *is_paused) {
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

			// Pause game if 'Space' key is pressed
			if (event.key.scancode == SDL_SCANCODE_SPACE) {
				*is_paused = !(*is_paused);
			}

			// Clear screen if 'c' key is pressed
			if (event.key.scancode == SDL_SCANCODE_C) {
				memset(game->gfx, 0, sizeof(game->gfx));
			}
			break;

		// Draw or erase if mouse down
		case SDL_EVENT_MOUSE_BUTTON_DOWN:
			// Draw
			if (event.button.button == SDL_BUTTON_LEFT) {
				is_left_mouse_down = true;
				int sim_x = event.button.x / WINDOW_SCALE;
				int sim_y = event.button.y / WINDOW_SCALE;
				draw_pixel_at(game->gfx, sim_x, sim_y, 1);
			}

			// Erase
			if (event.button.button == SDL_BUTTON_RIGHT) {
				is_right_mouse_down = true;
				int sim_x = event.button.x / WINDOW_SCALE;
				int sim_y = event.button.y / WINDOW_SCALE;
				draw_pixel_at(game->gfx, sim_x, sim_y, 0);
			}
			break;

		// Prevent draw on mouse up
		case SDL_EVENT_MOUSE_BUTTON_UP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				is_left_mouse_down = false;
			}
			if (event.button.button == SDL_BUTTON_RIGHT) {
				is_right_mouse_down = false;
			}
			break;

		// Continue draw if mouse down
		case SDL_EVENT_MOUSE_MOTION:
			if (is_left_mouse_down) {
				int sim_x = event.motion.x / WINDOW_SCALE;
				int sim_y = event.motion.y / WINDOW_SCALE;
				draw_pixel_at(game->gfx, sim_x, sim_y, 1);
			}

			if (is_right_mouse_down) {
				int sim_x = event.motion.x / WINDOW_SCALE;
				int sim_y = event.motion.y / WINDOW_SCALE;
				draw_pixel_at(game->gfx, sim_x, sim_y, 0);
			}
			break;
		}
	}
}
