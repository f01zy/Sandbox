#ifndef EVENTS_INCLUDED
#define EVENTS_INCLUDED

#include "types.h"
#include <SDL3/SDL.h>

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event);
void handle_events(struct AppContext *ctx);

#endif
