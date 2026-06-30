#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum ParticleType {
  PARTICLE_EMPTY,
  PARTICLE_SAND,
};

struct fVec2 {
  float x;
  float y;
};

struct Vec2 {
  int x;
  int y;
};

struct Particle {
  enum ParticleType type;
  struct fVec2 pos;
  struct fVec2 vel;
  bool is_updated;
};

struct GridItem {
  size_t particle;
};

struct Grid {
  struct Particle *parcticles;
  struct GridItem *buf;
};

struct Mouse {
  struct fVec2 pos;
  struct fVec2 vel;
  int size;
};

struct AppContext {
  struct SDL_Window *window;
  struct SDL_Renderer *renderer;
  struct SDL_Texture *screen_texture;
  struct Grid grid;
  struct Mouse mouse;
  struct Vec2 screen_size;
  uint32_t *color_buffer;
  size_t total_particles;
  float last_frame;
};

struct DrawParams {
  uint32_t *buf;
  struct Vec2 screen_size;
  size_t total_particles;
};

#endif
