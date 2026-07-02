#include "simulation/powder.h"
#include "simulation/particle.h"
#include "types.h"

void update_powder(struct AppContext *ctx, struct Particle *particle) {
  struct Vec2 pos = {(int)particle->pos.x, (int)particle->pos.y};
  struct Vec2 down_pos = {pos.x, pos.y + 1};
  struct Vec2 down_left_pos = {pos.x - 1, pos.y + 1};
  struct Vec2 down_right_pos = {pos.x + 1, pos.y + 1};
  if (pos.y >= ctx->screen_size.y - 1) return;
  if (!get_particle_by_position(&ctx->buffers, down_pos, ctx->screen_size)) {
    move_particle(&ctx->buffers, ctx->screen_size, pos, down_pos);
  } else if (pos.x < ctx->screen_size.x - 1 && !get_particle_by_position(&ctx->buffers, down_right_pos, ctx->screen_size)) {
    move_particle(&ctx->buffers, ctx->screen_size, pos, down_right_pos);
  } else if (pos.x > 0 && !get_particle_by_position(&ctx->buffers, down_left_pos, ctx->screen_size)) {
    move_particle(&ctx->buffers, ctx->screen_size, pos, down_left_pos);
  }
}
