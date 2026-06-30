#include "SDL3/SDL_events.h"
#define SDL_MAIN_USE_CALLBACKS 1

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "defines.h"
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
  struct AppContext *ctx = (struct AppContext *)SDL_malloc(sizeof(struct AppContext));
  initialize_context(ctx);
  SDL_HideCursor();
  *appstate = ctx;
  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate) {
  struct AppContext *ctx = (struct AppContext *)appstate;

  float deltatime = get_deltatime(ctx->last_frame);
  float need = 1.0f / FPS;
  if (deltatime >= need) {
    ctx->last_frame = SDL_GetTicks();
    SDL_SetRenderDrawColorFloat(ctx->renderer, 0.0f, 0.0f, 0.0f, 1.0f);
    SDL_RenderClear(ctx->renderer);
    iterate_grid(ctx);
    iterate_mouse(ctx);
    render(ctx);
    SDL_RenderPresent(ctx->renderer);
  }

  return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  struct AppContext *ctx = (struct AppContext *)appstate;
  if (event->type == SDL_EVENT_QUIT) {
    return SDL_APP_SUCCESS;
  } else if (event->type == SDL_EVENT_MOUSE_WHEEL) {
    ctx->mouse.size = CLAMP(ctx->mouse.size + event->wheel.y, 0, MAX_MOUSE_SIZE);
  }
  return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result) {
  struct AppContext *ctx = (struct AppContext *)appstate;
  SDL_DestroyTexture(ctx->screen_texture);
  SDL_free(ctx->grid.parcticles);
  SDL_free(ctx->grid.buf);
  SDL_free(ctx->color_buffer);
  SDL_free(ctx);
}
