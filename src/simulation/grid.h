#ifndef GRID_INCLUDED
#define GRID_INCLUDED

#include "types.h"

void iterate_grid(struct AppContext *ctx);
void draw_grid(const struct Particle *grid, const struct DrawParams *params);

#endif
