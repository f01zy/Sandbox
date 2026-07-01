#include <SDL3/SDL.h>
#include <stdint.h>
#include <stdlib.h>

#include "simulation/grid.h"
#include "types.h"
#include "utility/utility.h"

// TODO: под каждый тип частицы создать отдельные методы обновления, создания и т.п.
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
      // TODO: обработать крайние случаи
      struct Particle *particle = &ctx->grid[get_index_from_vector(ctx->screen_size, (struct Vec2){x, y})];
      struct Particle *bottom = &ctx->grid[get_index_from_vector(ctx->screen_size, (struct Vec2){x, y + 1})];
      struct Particle *left_bottom = &ctx->grid[get_index_from_vector(ctx->screen_size, (struct Vec2){x - 1, y + 1})];
      struct Particle *right_bottom = &ctx->grid[get_index_from_vector(ctx->screen_size, (struct Vec2){x + 1, y + 1})];
      switch (particle->type) {
      case PARTICLE_SAND:
        if (y < ctx->screen_size.y - 2) {
          if (bottom->type == PARTICLE_EMPTY) {
            swap_particles(particle, bottom);
          } else if (right_bottom->type == PARTICLE_EMPTY) {
            swap_particles(particle, right_bottom);
          } else if (left_bottom->type == PARTICLE_EMPTY) {
            swap_particles(particle, left_bottom);
          }
        }
        break;

      default:
        break;
      }
      x += stepX;
    }
  }
}

void draw_grid(const struct Particle *grid, const struct DrawParams *params) {
  for (int i = 0; i < params->total_particles; i++) {
    uint32_t color = get_color_from_type(grid[i].type);
    params->buf[i] = color;
  }
}
