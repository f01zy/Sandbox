#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include "types.h"

uint32_t get_color_from_type(enum ParticleType type);
size_t get_index_from_vector(struct Vec2 size, struct Vec2 pos);
float get_deltatime(float last);
int get_total_particles(struct Vec2 screen_size);

bool check_position(struct Vec2 screen_size, struct Vec2 pos);
void initialize_context(struct AppContext *ctx);
void clear_color_buffer(uint32_t *color_buffer, struct Vec2 screen_size);

#endif
