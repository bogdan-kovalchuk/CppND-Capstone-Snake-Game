#include "renderer.h"
#include <iostream>
#include <string>

Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width, const std::size_t grid_height)
    : screen_width_(screen_width),
      screen_height_(screen_height),
      grid_width_(grid_width),
      grid_height_(grid_height),
      sdl_window_(nullptr, SDL_DestroyWindow)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0)
  {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create Window
  sdl_window_.reset(SDL_CreateWindow("Snake Game", SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED, screen_width_,
                                     screen_height_, SDL_WINDOW_SHOWN));

  if (nullptr == sdl_window_)
  {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  sdl_renderer_ = SDL_CreateRenderer(sdl_window_.get(), -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer_)
  {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Initialize PNG loading
  int image_flag = IMG_INIT_PNG;
  if (!(IMG_Init(image_flag) & image_flag))
  {
    std::cerr << "SDL_image could not initialize.\n";
    std::cerr << "SDL_image Error: " << IMG_GetError() << "\n";
  }
}

Renderer::~Renderer()
{
  SDL_Quit();
}

void Renderer::Render(Snake const snake, SDL_Point const &food, Button &play_pause_button)
{
  SDL_Rect block;
  block.w = screen_width_ / grid_width_;
  block.h = screen_height_ / grid_height_;

  // Clear screen
  SDL_SetRenderDrawColor(sdl_renderer_, 0x1E, 0x1E, 0x1E, 0xFF);
  SDL_RenderClear(sdl_renderer_);

  // Render food
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0xCC, 0x00, 0xFF);
  block.x = food.x * block.w;
  block.y = food.y * block.h;
  SDL_RenderFillRect(sdl_renderer_, &block);

  // Render snake's body
  SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0xFF, 0xFF, 0xFF);
  for (SDL_Point const &point : snake.body)
  {
    block.x = point.x * block.w;
    block.y = point.y * block.h;
    SDL_RenderFillRect(sdl_renderer_, &block);
  }

  // Render snake's head
  block.x = static_cast<int>(snake.head_x) * block.w;
  block.y = static_cast<int>(snake.head_y) * block.h;
  if (snake.alive)
  {
    SDL_SetRenderDrawColor(sdl_renderer_, 0x00, 0x7A, 0xCC, 0xFF);
  }
  else
  {
    SDL_SetRenderDrawColor(sdl_renderer_, 0xFF, 0x00, 0x00, 0xFF);
  }
  SDL_RenderFillRect(sdl_renderer_, &block);

  // Render play/pause button
  play_pause_button.Render(sdl_renderer_);
  
  // Update Screen
  SDL_RenderPresent(sdl_renderer_);
}

void Renderer::UpdateWindowTitle(int score, int fps)
{
  std::string title{"Snake Score: " + std::to_string(score) + " FPS: " + std::to_string(fps)};
  SDL_SetWindowTitle(sdl_window_.get(), title.c_str());
}
