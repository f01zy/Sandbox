#include <SDL3/SDL.h>
#include <stdbool.h>
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

int get_total_particles(struct Vec2 screen_size) { return screen_size.x * screen_size.y; }

void initialize_context(struct AppContext *ctx) {
  ctx->screen_size = (struct Vec2){GRID_WIDTH, GRID_HEIGHT};
  int total_particles = get_total_particles(ctx->screen_size);
  if (!SDL_CreateWindowAndRenderer(TITLE, ctx->screen_size.x, ctx->screen_size.y, 0, &ctx->window, &ctx->renderer)) {
    SDL_Log("Failed to create window and renderer: %s\n", SDL_GetError());
    exit(-1);
  }
  ctx->screen_texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ctx->screen_size.x, ctx->screen_size.y);
  if (!ctx->screen_texture) {
    SDL_Log("Failed to create screen texture: %s\n", SDL_GetError());
    exit(-1);
  }
  ctx->buffers.grid = (struct GridItem *)SDL_calloc(total_particles, sizeof(struct GridItem));
  ctx->buffers.color_buffer = (uint32_t *)SDL_calloc(total_particles, sizeof(uint32_t));
  ctx->buffers.particles = (struct Particles){
    .buf = (struct Particle *)SDL_calloc(PARTICLES_LIMIT, sizeof(struct Particle)),
    .size = PARTICLES_LIMIT,
    .len = 0,
  };
  ctx->mouse.pos = (struct fVec2){ctx->screen_size.x / 2.0f, ctx->screen_size.y / 2.0f};
  ctx->mouse.size = 5;
  for (int i = 0; i < total_particles; i++) {
    ctx->buffers.grid[i].particle = -1;
  }
}

void clear_color_buffer(uint32_t *color_buffer, struct Vec2 screen_size) {
  size_t total_particles = get_total_particles(screen_size);
  for (int i = 0; i < total_particles; i++) {
    color_buffer[i] = MAKE_COLOR(0, 0, 0, 255);
  }
}

bool check_position(struct Vec2 screen_size, struct Vec2 pos) {
  if (pos.x >= 0 && pos.x < screen_size.x && pos.y >= 0 && pos.y < screen_size.y) return true;
  return false;
}
