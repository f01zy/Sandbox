#ifndef GRID_INCLUDED
#define GRID_INCLUDED

#include "types.h"

void iterate_grid(struct AppContext *ctx);
void draw_grid(const struct GridItem *grid, const struct Particles *particles, uint32_t *color_buffer, struct Vec2 screen_size);

#endif
