#ifndef WATER_INCLUDED
#define WATER_INCLUDED

#include "defines.h"
#include "types.h"

struct Particle water = {
  .name = "WATR",
  .desc = "Water. Conducts electricity, freezes, and extinguishes fires.",
  .state = PARTICLE_STATE_LIQUID,
  .type = PARTICLE_TYPE_WATER,
  .color = MAKE_COLOR(35, 137, 218, 255),
  .el = 0.0f,
  .weight = 0.03f,
  .is_color_distort = false,
};

#endif
