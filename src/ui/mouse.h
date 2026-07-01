#ifndef MOUSE_INCLUDED
#define MOUSE_INCLUDED

#include <stddef.h>
#include <stdint.h>

#include "types.h"

void draw_mouse(const struct Mouse *mouse, uint32_t *color_buffer, struct Vec2 screen_size);
void move_mouse(struct AppContext *ctx);

#endif
