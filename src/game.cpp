#include "game.h"
#include <iostream>
#include <SDL2/SDL.h>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake_(grid_width, grid_height),
      engine_(dev_()),
      random_w_(0, static_cast<int>(grid_width - 1)),
      random_h_(0, static_cast<int>(grid_height - 1))
{
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake_, play_pause_button_);

    if (play_pause_button_.GetState() == PRESSED)
    {
      Update();
    }

    renderer.Render(snake_, food_, play_pause_button_);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w_(engine_);
    y = random_h_(engine_);
    // Check that the location is not occupied by a snake item before placing food.
    if (!snake_.SnakeCell(x, y))
    {
      food_.x = x;
      food_.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if (!snake_.alive)
    return;

  snake_.Update();

  int new_x = static_cast<int>(snake_.head_x);
  int new_y = static_cast<int>(snake_.head_y);

  // Check if there's food over here
  if (food_.x == new_x && food_.y == new_y)
  {
    score++;
    PlaceFood();
    // Grow snake and increase speed.
    snake_.GrowBody();
    snake_.speed += 0.005;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake_.size; }