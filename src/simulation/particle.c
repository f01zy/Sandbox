#include "particle.h"
#include "types.h"
#include "utility/utility.h"

#include "simulation/elements/sand.h"
#include "simulation/elements/water.h"

struct Particle get_common_particle(enum ParticleType type) {
  switch (type) {
  case PARTICLE_TYPE_SAND:
    return sand;
  case PARTICLE_TYPE_WATER:
    return water;
  }
}

struct Particle *create_particle(struct Particles *particles) {
  if (particles->len >= particles->size - 1) return NULL;
  struct Particle *particle = &particles->buf[particles->len++];
  return particle;
}

void delete_particle() {}

struct Particle *get_particle_by_position(const struct Buffers *buffers, struct Vec2 pos, struct Vec2 screen_size) {
  if (!check_position(screen_size, pos)) return NULL;
  const struct GridItem *item = &buffers->grid[get_index_from_vector(screen_size, pos)];
  if (item->particle == -1) return NULL;
  return &buffers->particles.buf[item->particle];
}

void move_particle(const struct Buffers *buffers, struct Vec2 screen_size, struct Vec2 from, struct Vec2 to) {
  if (!check_position(screen_size, from) || !check_position(screen_size, to)) return;
  size_t index_from = get_index_from_vector(screen_size, from);
  size_t index_to = get_index_from_vector(screen_size, to);
  size_t particle_index = buffers->grid[index_from].particle;
  if (particle_index == -1) return;
  buffers->particles.buf[particle_index].pos = (struct fVec2){to.x, to.y};
  buffers->grid[index_to].particle = buffers->grid[index_from].particle;
  buffers->grid[index_from].particle = -1;
}

void spawn_particles(struct Buffers *buffers, const struct Mouse *mouse, struct Vec2 screen_size, enum ParticleType type) {
  float r = mouse->size;
  struct Vec4 bounds = {
    mouse->pos.x - r,
    mouse->pos.x + r,
    mouse->pos.y - r,
    mouse->pos.y + r,
  };
  for (int y = bounds.ay; y <= bounds.by; y++) {
    for (int x = bounds.ax; x <= bounds.bx; x++) {
      struct Vec2 pos = {x, y};
      if (!check_position(screen_size, pos)) continue;
      int dx = x - mouse->pos.x;
      int dy = y - mouse->pos.y;
      if ((dx * dx + dy * dy) <= r * r) {
        struct Particle *particle = get_particle_by_position(buffers, pos, screen_size);
        if (particle) continue;
        particle = create_particle(&buffers->particles);
        if (!particle) {
          SDL_Log("The particle limit has been reached\n");
          return;
        }
        *particle = get_common_particle(type);
        particle->pos = (struct fVec2){pos.x, pos.y};
        if (particle->is_color_distort) particle->color = get_distort_color(particle->color);
        buffers->grid[get_index_from_vector(screen_size, pos)].particle = buffers->particles.len - 1;
      }
    }
  }
}
