#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include "defines.h"
#include "types.h"
#include <stdint.h>

static struct {
  enum ParticleType type;
  uint32_t color;
} colors[] = {
  {PARTICLE_EMPTY, MAKE_COLOR(0, 0, 0, 255)},
  {PARTICLE_SAND, MAKE_COLOR(244, 164, 96, 255)},
};

#endif
