#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <SDL3/SDL.h>
#include <stdbool.h>
#include <stddef.h>

enum ParticleType {
  PARTICLE_EMPTY,
  PARTICLE_WALL,
  PARTICLE_LIQUID,
  PARTICLE_POWDER,
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
};

struct GridItem {
  size_t particle;
  bool is_updated;
  bool is_mouse;
};

struct Grid {
  struct Particle *pacticles;
  struct GridItem *buf;
  struct Vec2 size;
  size_t len;
};

struct Mouse {
  struct fVec2 pos;
  struct fVec2 vel;
  int size;
};

struct AppContext {
  SDL_Window *window;
  SDL_Renderer *renderer;
  struct Grid grid;
  struct Mouse mouse;
  float last;
};

#endif
