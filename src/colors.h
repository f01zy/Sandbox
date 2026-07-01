#ifndef COLORS_INCLUDED
#define COLORS_INCLUDED

#include "defines.h"
#include "types.h"
#include <stdint.h>

static struct {
  enum ParticleType type;
  uint32_t color;
} colors[] = {
  {PARTICLE_SAND, MAKE_COLOR(244, 164, 96, 255)},
};

#endif
