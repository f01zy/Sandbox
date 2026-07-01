#ifndef GRID_INCLUDED
#define GRID_INCLUDED

#include "types.h"

void iterate_grid(struct AppContext *ctx);
void draw_grid(const struct Buffers *buffers, struct Vec2 screen_size);

#endif
