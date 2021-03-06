#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL2/SDL.h>

#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "button.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;

private:
  Snake snake_;
  SDL_Point food_;
  Button play_pause_button_;

  std::random_device dev_;
  std::mt19937 engine_;
  std::uniform_int_distribution<int> random_w_;
  std::uniform_int_distribution<int> random_h_;

  int score{0};

  void PlaceFood();
  void Update();
};

#endif