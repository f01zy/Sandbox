#include <SDL3/SDL.h>
#include <math.h>

#include "defines.h"
#include "types.h"
#include "ui/mouse.h"
#include "utility/utility.h"

void draw_mouse(const struct Mouse *mouse, const struct DrawParams *params) {
  int angle = 0;
  while (angle <= 360) {
    struct fVec2 offset = {
      mouse->size * cos(angle),
      mouse->size * sin(angle),
    };
    struct Vec2 pos = {
      (int)(mouse->pos.x + offset.x),
      (int)(mouse->pos.y + offset.y),
    };
    if (check_position(params->screen_size, pos)) {
      size_t index = get_index_from_vector(params->screen_size, pos);
      params->buf[index] = MAKE_COLOR(255, 255, 255, 255);
    }
    angle++;
  }
}

void move_mouse(struct AppContext *ctx) {
  struct fVec2 target;
  uint32_t state = SDL_GetMouseState(&target.x, &target.y);
  struct fVec2 delta = {
    target.x - ctx->mouse.pos.x,
    target.y - ctx->mouse.pos.y,
  };
  ctx->mouse.pos.x += delta.x * MOUSE_COEFFICIENT;
  ctx->mouse.pos.y += delta.y * MOUSE_COEFFICIENT;
}
