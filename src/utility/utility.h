#ifndef UTILITY_INCLUDED
#define UTILITY_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include "types.h"

struct Vec2 fvec2_to_vec2(struct fVec2 vec);
struct fVec2 vec2_to_fvec2(struct Vec2 vec);
uint32_t get_distort_color(uint32_t color);
size_t get_index_from_vector(struct Vec2 screen_size, struct Vec2 pos);
float get_deltatime(float last);
int get_total_particles(struct Vec2 screen_size);

bool compare_vec2(struct Vec2 a, struct Vec2 b);
bool check_position(struct Vec2 screen_size, struct Vec2 pos);
void initialize_context(struct AppContext *ctx);
void clear_color_buffer(uint32_t *color_buffer, struct Vec2 screen_size);

#endif
