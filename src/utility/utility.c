#include <SDL3/SDL.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "colors.h"
#include "defines.h"
#include "utility/utility.h"

uint32_t get_color_from_type(enum ParticleType type) {
  for (int i = 0; i < sizeof(colors) / sizeof(colors[0]); i++) {
    if (colors[i].type == type) return colors[i].color;
  }
  return MAKE_COLOR(0, 0, 0, 255);
}

size_t get_index_from_vector(struct Vec2 size, struct Vec2 pos) { return pos.y * size.x + pos.x; }
float get_deltatime(float last) { return (SDL_GetTicks() - last) / 1000.0f; }

void initialize_context(struct AppContext *ctx) {
  // Size
  ctx->screen_size = (struct Vec2){GRID_WIDTH, GRID_HEIGHT};
  ctx->total_particles = ctx->screen_size.x * ctx->screen_size.y;

  // Window
  if (!SDL_CreateWindowAndRenderer(TITLE, ctx->screen_size.x, ctx->screen_size.y, 0, &ctx->window, &ctx->renderer)) {
    SDL_Log("Failed to create window and renderer: %s\n", SDL_GetError());
    exit(-1);
  }

  // Assets
  ctx->screen_texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ctx->screen_size.x, ctx->screen_size.y);
  if (!ctx->screen_texture) {
    SDL_Log("Failed to create screen texture: %s\n", SDL_GetError());
    exit(-1);
  }

  // Buffers
  ctx->grid.buf = (struct GridItem *)SDL_calloc(ctx->total_particles, sizeof(struct GridItem));
  ctx->grid.parcticles = (struct Particle *)SDL_calloc(ctx->total_particles, sizeof(struct Particle));
  ctx->color_buffer = (uint32_t *)SDL_calloc(ctx->total_particles, sizeof(uint32_t));
  for (int i = 0; i < ctx->total_particles; i++) {
    ctx->grid.parcticles->type = PARTICLE_EMPTY;
    ctx->grid.buf->particle = -1;
  }

  // Mouse
  ctx->mouse.pos = (struct fVec2){ctx->screen_size.x / 2.0f, ctx->screen_size.y / 2.0f};
  ctx->mouse.size = 5;
}
