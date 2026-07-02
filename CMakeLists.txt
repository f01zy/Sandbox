cmake_minimum_required(VERSION 3.5)
project(Sandbox)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(TARGET sandbox)
set(SOURCE
  ./src/core/main.c
  ./src/core/events.c
  ./src/simulation/grid.c
  ./src/simulation/particle.c
  ./src/simulation/powder.c
  ./src/simulation/liquid.c
  ./src/simulation/physics.c
  ./src/ui/mouse.c
  ./src/ui/hud.c
  ./src/ui/text.c
  ./src/graphics/renderer.c
  ./src/utility/utility.c
)

add_subdirectory(./third_party/SDL EXCLUDE_FROM_ALL)
add_subdirectory(./third_party/SDL_ttf EXCLUDE_FROM_ALL)
add_executable(${TARGET} ${SOURCE})
target_include_directories(${TARGET} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(${TARGET} PRIVATE
  SDL3_ttf::SDL3_ttf
  SDL3::SDL3
  m
)
