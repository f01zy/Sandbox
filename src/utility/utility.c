#include <SDL3/SDL.h>
#include <stddef.h>

#include "defines.h"
#include "utility/utility.h"

size_t get_index_from_vector(struct Vec2 size, struct Vec2 pos) { return pos.y * size.x + pos.x; }

float get_deltatime(float last) { return (SDL_GetTicks() - last) / 1000.0f; }

void initialize_grid(struct Grid *grid) {
  grid->size = (struct Vec2){GRID_WIDTH, GRID_HEIGHT};
  grid->len = grid->size.x * grid->size.y;
  grid->buf = (struct GridItem *)SDL_calloc(grid->len, sizeof(struct GridItem));
  grid->pacticles = (struct Particle *)SDL_calloc(grid->len, sizeof(struct Particle));
  for (int i = 0; i < grid->len; i++) {
    grid->pacticles->type = PARTICLE_EMPTY;
    grid->buf->particle = -1;
  }
}

void initialize_context(struct AppContext *ctx) { initialize_grid(&ctx->grid); }

void reset_grid_flags(struct Grid *grid) {
  for (int i = 0; i < grid->size.x * grid->size.y; i++) {
    grid->buf[i].is_mouse = false;
    grid->buf[i].is_updated = false;
  }
}
