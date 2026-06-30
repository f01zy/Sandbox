#include <SDL3/SDL.h>
#include <math.h>

#include "ui/mouse.h"
#include "utility/utility.h"

void draw_mouse(struct AppContext *ctx) {
  int angle = 0;
  while (angle <= 360) {
    struct fVec2 offset = {
      ctx->mouse.size * cos(angle),
      ctx->mouse.size * sin(angle),
    };
    struct Vec2 pos = {
      (int)(ctx->mouse.pos.x + offset.x),
      (int)(ctx->mouse.pos.y + offset.y),
    };
    size_t index = get_index_from_vector(ctx->grid.size, pos);
    if (index >= 0 && index < ctx->grid.len) ctx->grid.buf[index].is_mouse = true;
    angle++;
  }
}
