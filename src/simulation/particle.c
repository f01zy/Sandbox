#include "particle.h"
#include "types.h"
#include "utility/utility.h"

#include "simulation/elements/sand.h"
#include "simulation/elements/water.h"
#include <stdlib.h>

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

bool grid_raycast(struct Buffers *buffers, struct Vec2 screen_size, struct Vec2 from, struct Vec2 to, struct Vec2 *collision_pos) {
  int ax = from.x, ay = from.y;
  int bx = to.x, by = to.y;
  int dx = abs(ax - bx);
  int dy = abs(ay - by);
  int sx = ax > bx ? -1 : 1;
  int sy = ay > by ? -1 : 1;
  int err = dx - dy;
  int x = ax;
  int y = ay;
  while (1) {
    int prev_x = x;
    int prev_y = y;
    int tmp = err * 2;
    if (tmp > -dy) {
      err -= dy;
      x += sx;
    }
    if (tmp < dx) {
      err += dx;
      y += sy;
    }
    if (x != prev_x && y != prev_y) {
      struct Vec2 side1 = {x, prev_y};
      struct Vec2 side2 = {prev_x, y};
      if (get_particle_by_position(buffers, side1, screen_size)) {
        *collision_pos = side1;
        return true;
      }
      if (get_particle_by_position(buffers, side2, screen_size)) {
        *collision_pos = side2;
        return true;
      }
    }
    struct Vec2 curr = {x, y};
    if (get_particle_by_position(buffers, curr, screen_size)) {
      *collision_pos = curr;
      return true;
    }
    if (x == bx && y == by) break;
  }
  return false;
}

struct Particle *get_particle_by_position(const struct Buffers *buffers, struct Vec2 pos, struct Vec2 screen_size) {
  if (!check_position(screen_size, pos)) return NULL;
  const struct GridItem *item = &buffers->grid[get_index_from_vector(screen_size, pos)];
  if (item->particle == -1) return NULL;
  return &buffers->particles.buf[item->particle];
}

void move_particle(const struct Buffers *buffers, struct Vec2 screen_size, struct Vec2 from, struct fVec2 to) {
  struct Vec2 projected_to = fvec2_to_vec2(to);
  if (!check_position(screen_size, from) || !check_position(screen_size, projected_to)) return;
  size_t index_from = get_index_from_vector(screen_size, from);
  size_t index_to = get_index_from_vector(screen_size, projected_to);
  size_t particle_from_index = buffers->grid[index_from].particle;
  size_t particle_to_index = buffers->grid[index_to].particle;
  if (particle_from_index == -1 || particle_to_index != -1) return;
  buffers->particles.buf[particle_from_index].pos = to;
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
        particle->vel = (struct fVec2){0.0f, 0.0f};
        if (particle->is_color_distort) particle->color = get_distort_color(particle->color);
        buffers->grid[get_index_from_vector(screen_size, pos)].particle = buffers->particles.len - 1;
      }
    }
  }
}
