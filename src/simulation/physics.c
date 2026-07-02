#include "simulation/physics.h"
#include "defines.h"
#include "types.h"

void apply_gravity(struct AppContext *ctx, struct Particle *particle) { particle->vel.y += ACCELERATION_OF_GRAVITY * ctx->timers.deltatime; }

void collide_particles(struct Particle *a, struct Particle *b) {
  float total_el = (a->el + b->el) / 2.0f;
  float tmp1 = 1 + total_el;
  float tmp2 = a->weight + b->weight;
  float new_a_vx = (a->vel.x * (a->weight - b->weight * total_el) + (b->weight * b->vel.x * tmp1)) / tmp2;
  float new_a_vy = (a->vel.y * (a->weight - b->weight * total_el) + (b->weight * b->vel.y * tmp1)) / tmp2;
  float new_b_vx = (b->vel.x * (b->weight - a->weight * total_el) + (a->weight * a->vel.x * tmp1)) / tmp2;
  float new_b_vy = (b->vel.y * (b->weight - a->weight * total_el) + (a->weight * a->vel.y * tmp1)) / tmp2;
  a->vel = (struct fVec2){new_a_vx, new_a_vy};
  b->vel = (struct fVec2){new_b_vx, new_b_vy};
}
