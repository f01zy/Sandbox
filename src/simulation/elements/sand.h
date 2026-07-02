#ifndef SAND_INCLUDED
#define SAND_INCLUDED

#include "defines.h"
#include "types.h"

struct Particle sand = {
  .name = "SAND",
  .desc = "Sand, Heavy particles. Melts into glass.",
  .state = PARTICLE_STATE_POWDER,
  .type = PARTICLE_TYPE_SAND,
  .color = MAKE_COLOR(244, 164, 96, 255),
  .el = 0.05f,
  .weight = 0.09f,
  .is_color_distort = true,
};

#endif
