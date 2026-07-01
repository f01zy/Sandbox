#ifndef PARTICLES_INCLUDED
#define PARTICLES_INCLUDED

#include "types.h"

struct Particle *get_particle_by_position(const struct GridItem *grid, const struct Particles *particles, struct Vec2 pos, struct Vec2 screen_size);
void spawn_particles(const struct Mouse *mouse, struct GridItem *grid, struct Particles *particles, struct Vec2 screen_size);
void move_particle(struct GridItem *grid, struct Particles *particles, struct Vec2 screen_size, struct Vec2 from, struct Vec2 to);

#endif
