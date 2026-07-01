#include <SDL3/SDL.h>
#include <stddef.h>
#include <stdio.h>

#include "types.h"
#include "ui/hud.h"
#include "ui/text.h"

void render_hud(struct AppContext *ctx) {
  float fps = 1 / ctx->timers.deltatime;
  char buf[32];
  size_t len = snprintf(buf, sizeof(buf) - 1, "FPS: %.2f", fps);
  buf[len] = '\0';
  struct SDL_Color color = {255, 255, 255, 255};
  struct Vec2 pos = {20, 20};
  render_text(ctx->renderer, ctx->resources.font, buf, len, color, pos);
}
