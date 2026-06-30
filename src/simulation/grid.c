#include <SDL3/SDL.h>
#include <stdint.h>

#include "simulation/grid.h"
#include "types.h"
#include "utility/utility.h"

void iterate_grid(struct AppContext *ctx) {}

void draw_grid(const struct Grid *grid, const struct DrawParams *params) {
  for (int i = 0; i < params->total_particles; i++) {
    size_t index = grid->buf[i].particle;
    if (index == -1) continue;
    struct Particle *particle = &grid->parcticles[index];
    uint32_t color = get_color_from_type(particle->type);
    params->buf[i] = color;
  }
}
