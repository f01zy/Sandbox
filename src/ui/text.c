#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdlib.h>

#include "ui/text.h"

void render_text(struct SDL_Renderer *renderer, struct TTF_Font *font, const char *text, size_t len, struct SDL_Color color, struct Vec2 pos) {
  SDL_Surface *surface = TTF_RenderText_Solid(font, text, len, color);
  SDL_Texture *texture;
  if (surface) {
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
  }
  if (!texture) {
    SDL_Log("Failed to create text texture: %s\n", SDL_GetError());
    exit(-1);
  }
  float w, h;
  SDL_GetTextureSize(texture, &w, &h);
  SDL_FRect dstrect = {
    pos.x,
    pos.y,
    w,
    h,
  };
  SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_LINEAR);
  SDL_RenderTexture(renderer, texture, NULL, &dstrect);
  SDL_DestroyTexture(texture);
}
