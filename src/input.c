#include "input.h"

#include <SDL3/SDL.h>

void process_input(bool *is_running) {
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
		}
	}
}
