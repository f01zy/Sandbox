#ifndef TEXT_INCLUDED
#define TEXT_INCLUDED

#include <SDL3_ttf/SDL_ttf.h>
#include <stddef.h>

#include "types.h"

void render_text(struct SDL_Renderer *renderer, struct TTF_Font *font, const char *text, size_t len, struct SDL_Color color, struct Vec2 pos);

#endif
