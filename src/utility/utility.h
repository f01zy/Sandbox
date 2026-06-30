#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include "types.h"
#include <stddef.h>

size_t get_index_from_vector(struct Vec2 size, struct Vec2 pos);
float get_deltatime(float last);
void initialize_context(struct AppContext *ctx);
void reset_grid_flags(struct Grid *grid);

#endif
