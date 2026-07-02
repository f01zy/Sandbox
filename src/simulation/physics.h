#ifndef PHYSICS_INCLUDED
#define PHYSICS_INCLUDED

#include "types.h"

void apply_gravity(struct AppContext *ctx, struct Particle *particle);
void collide_particles(struct Particle *a, struct Particle *b);

#endif
