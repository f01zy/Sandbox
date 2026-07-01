#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include "types.h"

bool check_position(struct Vec2 screen_size, struct Vec2 pos);
uint32_t get_color_from_type(enum ParticleType type);
size_t get_index_from_vector(struct Vec2 size, struct Vec2 pos);
float get_deltatime(float last);
void initialize_context(struct AppContext *ctx);
void swap_particles(struct Particle *a, struct Particle *b);

#endif
