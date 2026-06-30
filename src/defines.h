#ifndef DEFINES_INCLUDED
#define DEFINES_INCLUDED

#define TITLE                  "Sandbox"
#define GRID_WIDTH             611
#define GRID_HEIGHT            383
#define FPS                    60

#define MOUSE_COEFFICIENT      0.3f
#define MAX_MOUSE_SIZE         50

#define MAKE_COLOR(R, G, B, A) (((uint32_t)(R) << 24) | ((uint32_t)(G) << 16) | ((uint32_t)(B) << 8) | ((uint32_t)(A)))
#define CLAMP(A, B, C)         ((A) < (B) ? (B) : (A) > (C) ? (C) : (A))

#endif
