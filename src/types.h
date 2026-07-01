#ifndef TYPES_INCLUDED
#define TYPES_INCLUDED

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum ParticleType {
  PARTICLE_NOTHING,
  PARTICLE_SAND,
};

struct Color {
  enum ParticleType type;
  uint8_t r, g, b, a;
};

struct fVec2 {
  float x;
  float y;
};

struct Vec2 {
  int x;
  int y;
};

struct Vec4 {
  int ax, bx;
  int ay, by;
};

struct Particle {
  enum ParticleType type;
  struct fVec2 pos;
  struct fVec2 vel;
  uint32_t color;
  bool is_updated;
};

struct Particles {
  struct Particle *buf;
  size_t size;
  size_t len;
};

struct GridItem {
  size_t particle;
};

struct Mouse {
  struct fVec2 pos;
  struct fVec2 vel;
  bool is_left_button_pressed;
  bool is_right_button_pressed;
  int size;
};

struct Buffers {
  struct Particles particles;
  struct GridItem *grid;
  uint32_t *color_buffer;
};

struct Resources {
  struct SDL_Texture *screen_texture;
  struct TTF_Font *font;
};

struct Timers {
  float lastframe;
  float deltatime;
};

struct AppContext {
  struct SDL_Window *window;
  struct SDL_Renderer *renderer;
  struct Resources resources;
  struct Buffers buffers;
  struct Mouse mouse;
  struct Timers timers;
  struct Vec2 screen_size;
};

struct DrawParams {
  uint32_t *color_buffer;
  struct Vec2 screen_size;
};

#endif
