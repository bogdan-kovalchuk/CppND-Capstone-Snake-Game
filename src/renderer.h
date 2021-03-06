#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "snake.h"
#include "button.h"

class Renderer
{
public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food, Button &play_pause_button);
  void UpdateWindowTitle(int score, int fps);

private:
  std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> sdl_window_;
  SDL_Renderer *sdl_renderer_;

  const std::size_t screen_width_;
  const std::size_t screen_height_;
  const std::size_t grid_width_;
  const std::size_t grid_height_;
};

#endif