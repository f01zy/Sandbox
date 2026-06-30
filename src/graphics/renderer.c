#include "graphics/renderer.h"
#include "simulation/grid.h"
#include "types.h"
#include "ui/mouse.h"

void render(struct AppContext *ctx) {
  struct DrawParams params = {
    ctx->color_buffer,
    ctx->screen_size,
    ctx->total_particles,
  };
  draw_grid(&ctx->grid, &params);
  draw_mouse(&ctx->mouse, &params);
  struct SDL_FRect destrect = {0, 0, ctx->screen_size.x, ctx->screen_size.y};
  SDL_UpdateTexture(ctx->screen_texture, NULL, ctx->color_buffer, ctx->screen_size.x * sizeof(uint32_t));
  SDL_RenderTexture(ctx->renderer, ctx->screen_texture, NULL, &destrect);
}
