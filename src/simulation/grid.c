#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdlib.h>

#include "simulation/grid.h"
#include "simulation/particles.h"
#include "types.h"
#include "utility/utility.h"

void iterate_grid(struct AppContext *ctx) {
  int startX, endX, stepX;
  if (rand() % 2) {
    startX = 0;
    endX = ctx->screen_size.x - 1;
    stepX = 1;
  } else {
    startX = ctx->screen_size.x - 1;
    endX = 0;
    stepX = -1;
  }
  for (int y = ctx->screen_size.y - 1; y >= 0; y--) {
    int x = startX;
    while (x != endX) {
      struct Vec2 current_pos = {x, y};
      int idx = ctx->buffers.grid[get_index_from_vector(ctx->screen_size, current_pos)].particle;
      if (idx == -1) {
        x += stepX;
        continue;
      }
      struct Particle *particle = &ctx->buffers.particles.buf[idx];
      switch (particle->type) {
      case PARTICLE_SAND:
        if (y >= ctx->screen_size.y - 1) break;
        struct Vec2 down_pos = {x, y + 1};
        struct Vec2 down_left_pos = {x - 1, y + 1};
        struct Vec2 down_right_pos = {x + 1, y + 1};
        struct Particle *down = get_particle_by_position(ctx->buffers.grid, &ctx->buffers.particles, down_pos, ctx->screen_size);
        struct Particle *down_left = get_particle_by_position(ctx->buffers.grid, &ctx->buffers.particles, down_left_pos, ctx->screen_size);
        struct Particle *down_right = get_particle_by_position(ctx->buffers.grid, &ctx->buffers.particles, down_right_pos, ctx->screen_size);
        if (!down) {
          move_particle(ctx->buffers.grid, &ctx->buffers.particles, ctx->screen_size, current_pos, down_pos);
        } else if (x < ctx->screen_size.x - 1 && !down_right) {
          move_particle(ctx->buffers.grid, &ctx->buffers.particles, ctx->screen_size, current_pos, down_right_pos);
        } else if (x > 0 && !down_left) {
          move_particle(ctx->buffers.grid, &ctx->buffers.particles, ctx->screen_size, current_pos, down_left_pos);
        }
        break;
      }
      x += stepX;
    }
  }
}

void draw_grid(const struct GridItem *grid, const struct Particles *particles, uint32_t *color_buffer, struct Vec2 screen_size) {
  for (int y = 0; y < screen_size.y; y++) {
    for (int x = 0; x < screen_size.x; x++) {
      struct Vec2 pos = {x, y};
      struct Particle *particle = get_particle_by_position(grid, particles, pos, screen_size);
      if (!particle) continue;
      uint32_t color = get_color_from_type(particle->type);
      color_buffer[get_index_from_vector(screen_size, pos)] = color;
    }
  }
}
