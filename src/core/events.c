#include <SDL3/SDL.h>

#include "core/events.h"
#include "defines.h"
#include "simulation/particle.h"
#include "types.h"

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event) {
  struct AppContext *ctx = (struct AppContext *)appstate;
  switch (event->type) {
  case SDL_EVENT_QUIT:
    return SDL_APP_SUCCESS;

  case SDL_EVENT_MOUSE_WHEEL:
    ctx->mouse.size = CLAMP(ctx->mouse.size + event->wheel.y, 0, MAX_MOUSE_SIZE);
    break;

  case SDL_EVENT_MOUSE_BUTTON_DOWN:
  case SDL_EVENT_MOUSE_BUTTON_UP:
    bool state = event->type == SDL_EVENT_MOUSE_BUTTON_DOWN;
    if (event->button.button == SDL_BUTTON_LEFT) {
      ctx->mouse.is_left_button_pressed = state;
    } else if (event->button.button == SDL_BUTTON_RIGHT) {
      ctx->mouse.is_right_button_pressed = state;
    }
    break;
  }

  return SDL_APP_CONTINUE;
}

void handle_events(struct AppContext *ctx) {
  if (ctx->mouse.is_left_button_pressed) spawn_particles(&ctx->buffers, &ctx->mouse, ctx->screen_size, ctx->curr_particle);
}
