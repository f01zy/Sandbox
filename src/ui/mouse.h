#ifndef MOUSE_INCLUDED
#define MOUSE_INCLUDED

#include "types.h"
#include <stddef.h>

void draw_mouse(const struct Mouse *mouse, const struct DrawParams *params);
void iterate_mouse(struct AppContext *ctx);

#endif
