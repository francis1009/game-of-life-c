#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "game.h"

void input_process(Game *game, bool *is_running, bool *is_paused);

#endif
