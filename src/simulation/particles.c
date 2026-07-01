#include "particles.h"
#include "utility/utility.h"

void spawn_particles(struct Particle *grid, const struct Mouse *mouse, struct Vec2 screen_size) {
  float r = mouse->size;
  struct Vec4 bounds = {
    mouse->pos.x - r,
    mouse->pos.x + r,
    mouse->pos.y - r,
    mouse->pos.y + r,
  };
  for (int y = bounds.ay; y < bounds.by; y++) {
    for (int x = bounds.ax; x < bounds.bx; x++) {
      struct Vec2 pos = {x, y};
      if (!check_position(screen_size, pos)) continue;
      int dx = x - mouse->pos.x;
      int dy = y - mouse->pos.y;
      if ((dx * dx + dy * dy) <= r * r) grid[get_index_from_vector(screen_size, pos)].type = PARTICLE_SAND;
    }
  }
}
