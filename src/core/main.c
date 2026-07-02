#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>
#include <time.h>

#include "defines.h"
#include "events.h"
#include "graphics/renderer.h"
#include "simulation/grid.h"
#include "types.h"
#include "ui/mouse.h"
#include "utility/utility.h"

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv) {
  SDL_SetAppMetadata("Sandbox", "0.0.1", NULL);
  if (!SDL_Init(SDL_INIT_VIDEO)) {
    SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  if (!TTF_Init()) {
    SDL_Log("Failed to initialize SDL_ttf: %s\n", SDL_GetError());
    return SDL_APP_FAILURE;
  }
  struct AppContext *ctx = (struct AppContext *)SDL_calloc(1, sizeof(struct AppContext));
  initialize_context(ctx);
  srand(time(NULL));
  *appstate = ctx;
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  struct AppContext *ctx = (struct AppContext *)appstate;
  handle_events(ctx);
  float deltatime = get_deltatime(ctx->timers.lastframe);
  double need = 1.0f / FPS;
  if (deltatime >= need) {
    ctx->timers.lastframe = SDL_GetTicks();
    ctx->timers.deltatime = deltatime;

    // Clear screen
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_FRect level_rect = {0, 0, ctx->screen_size.x, ctx->screen_size.y};
    SDL_RenderFillRect(ctx->renderer, &level_rect);

    // Render sandbox
    iterate_grid(ctx);
    move_mouse(ctx);
    render(ctx);

    SDL_RenderPresent(ctx->renderer);
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  struct AppContext *ctx = (struct AppContext *)appstate;
  TTF_CloseFont(ctx->resources.font);
  SDL_DestroyTexture(ctx->resources.screen_texture);
  SDL_free(ctx->buffers.grid);
  SDL_free(ctx->buffers.color_buffer);
  SDL_free(ctx->buffers.particles.buf);
  SDL_free(ctx);
}
