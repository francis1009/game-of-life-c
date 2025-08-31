#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdbool.h>

bool display_init(void);
void display_draw(unsigned char gfx[]);
void display_destroy(void);

#endif
