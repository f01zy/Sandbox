#include "simulation/powder.h"
#include "simulation/particle.h"
#include "simulation/physics.h"
#include "types.h"
#include "utility/utility.h"

void slide_powder(struct AppContext *ctx, struct Particle *particle) {
  struct Vec2 pos = {(int)particle->pos.x, (int)particle->pos.y};
  if (pos.y >= ctx->screen_size.y - 1) return;
  struct Vec2 down_pos = {pos.x, pos.y + 1};
  struct Vec2 down_left_pos = {pos.x - 1, pos.y + 1};
  struct Vec2 down_right_pos = {pos.x + 1, pos.y + 1};
  if (!get_particle_by_position(&ctx->buffers, down_pos, ctx->screen_size)) {
    move_particle(&ctx->buffers, ctx->screen_size, pos, vec2_to_fvec2(down_pos));
  } else if (pos.x < ctx->screen_size.x - 1 && !get_particle_by_position(&ctx->buffers, down_right_pos, ctx->screen_size)) {
    move_particle(&ctx->buffers, ctx->screen_size, pos, vec2_to_fvec2(down_right_pos));
  } else if (pos.x > 0 && !get_particle_by_position(&ctx->buffers, down_left_pos, ctx->screen_size)) {
    move_particle(&ctx->buffers, ctx->screen_size, pos, vec2_to_fvec2(down_left_pos));
  }
}

void update_powder(struct AppContext *ctx, struct Particle *particle) {
  apply_gravity(ctx, particle);
  struct fVec2 next_pos = {
    particle->pos.x + particle->vel.x * ctx->timers.deltatime,
    particle->pos.y + particle->vel.y * ctx->timers.deltatime,
  };
  struct Vec2 projected_next_pos = fvec2_to_vec2(next_pos);
  struct Vec2 projected_curr_pos = fvec2_to_vec2(particle->pos);
  if (compare_vec2(projected_curr_pos, projected_next_pos)) {
    particle->pos = next_pos;
    return;
  }
  struct Vec2 collision_pos;
  if (grid_raycast(&ctx->buffers, ctx->screen_size, projected_curr_pos, projected_next_pos, &collision_pos)) {
    size_t target_idx = get_index_from_vector(ctx->screen_size, collision_pos);
    if (target_idx != -1) {
      struct Particle *target = &ctx->buffers.particles.buf[target_idx];
      collide_particles(particle, target);
    }
    slide_powder(ctx, particle);
  } else {
    move_particle(&ctx->buffers, ctx->screen_size, projected_curr_pos, next_pos);
  }
}
