#ifndef PARTICLES_INCLUDED
#define PARTICLES_INCLUDED

#include "types.h"

struct Particle get_common_particle(enum ParticleType type);
struct Particle *get_particle_by_position(const struct Buffers *buffers, struct Vec2 pos, struct Vec2 screen_size);
void spawn_particles(struct Buffers *buffers, const struct Mouse *mouse, struct Vec2 screen_size, enum ParticleType type);
void move_particle(const struct Buffers *buffers, struct Vec2 screen_size, struct Vec2 from, struct Vec2 to);

#endif
