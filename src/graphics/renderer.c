#include "graphics/renderer.h"
#include "simulation/grid.h"
#include "types.h"
#include "ui/mouse.h"
#include "utility/utility.h"

void render(struct AppContext *ctx) {
  struct SDL_FRect destrect = {0, 0, ctx->screen_size.x, ctx->screen_size.y};
  clear_color_buffer(ctx->buffers.color_buffer, ctx->screen_size);
  draw_grid(ctx->buffers.grid, &ctx->buffers.particles, ctx->buffers.color_buffer, ctx->screen_size);
  draw_mouse(&ctx->mouse, ctx->buffers.color_buffer, ctx->screen_size);
  SDL_UpdateTexture(ctx->screen_texture, NULL, ctx->buffers.color_buffer, ctx->screen_size.x * sizeof(uint32_t));
  SDL_RenderTexture(ctx->renderer, ctx->screen_texture, NULL, &destrect);
}
