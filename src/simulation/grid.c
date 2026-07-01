#include <SDL3/SDL.h>
#include <stdlib.h>

#include "simulation/grid.h"
#include "simulation/particles.h"
#include "types.h"
#include "utility/utility.h"

void iterate_grid(struct AppContext *ctx) {
  bool is_right = rand() % 2;
  int startX = is_right ? ctx->screen_size.x - 1 : 0;
  int endX = is_right ? 0 : ctx->screen_size.x - 1;
  int stepX = is_right ? -1 : 1;
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
      struct Vec2 down_pos = {x, y + 1};
      struct Vec2 down_left_pos = {x - 1, y + 1};
      struct Vec2 down_right_pos = {x + 1, y + 1};
      switch (particle->type) {
      case PARTICLE_SAND:
        if (y >= ctx->screen_size.y - 1) break;
        if (!get_particle_by_position(&ctx->buffers, down_pos, ctx->screen_size)) {
          move_particle(&ctx->buffers, ctx->screen_size, current_pos, down_pos);
        } else if (x < ctx->screen_size.x - 1 && !get_particle_by_position(&ctx->buffers, down_right_pos, ctx->screen_size)) {
          move_particle(&ctx->buffers, ctx->screen_size, current_pos, down_right_pos);
        } else if (x > 0 && !get_particle_by_position(&ctx->buffers, down_left_pos, ctx->screen_size)) {
          move_particle(&ctx->buffers, ctx->screen_size, current_pos, down_left_pos);
        }
        break;
      default:
        break;
      }
      x += stepX;
    }
  }
}

void draw_grid(const struct Buffers *buffers, struct Vec2 screen_size) {
  for (int y = 0; y < screen_size.y; y++) {
    for (int x = 0; x < screen_size.x; x++) {
      struct Vec2 pos = {x, y};
      struct Particle *particle = get_particle_by_position(buffers, pos, screen_size);
      if (particle) buffers->color_buffer[get_index_from_vector(screen_size, pos)] = particle->color;
    }
  }
}
