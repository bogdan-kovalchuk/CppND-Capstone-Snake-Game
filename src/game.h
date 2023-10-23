#ifndef GAME_H
#define GAME_H

#include <random>
#include <SDL2/SDL.h>

#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "button.h"
#include "pause_state.h"
#include "score_tracker.h"
#include "update_guard.h"

class Game
{
public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  void Restart();

private:
  Snake snake_;
  SDL_Point food_;
  bool food_valid_{false};
  Button play_pause_button_;
  TickGuard pause_state_;
  UpdateGuard update_guard_;

  std::size_t grid_width_;
  std::size_t grid_height_;

  std::random_device dev_;
  std::mt19937 engine_;
  std::uniform_int_distribution<int> random_w_;
  std::uniform_int_distribution<int> random_h_;

  ScoreTracker score_tracker_;

  void PlaceFood();
  void Update();
};

#endif