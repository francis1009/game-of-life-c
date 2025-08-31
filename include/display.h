#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

#include "game.h"

bool display_init(void);
void display_draw(const Game *game);
void display_destroy(void);

#endif
