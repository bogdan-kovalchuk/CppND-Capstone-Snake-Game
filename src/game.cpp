#include "game.h"
#include "food_placer.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace
{
constexpr int kMaxFoodPlacementAttempts = 100;
}

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake_(grid_width, grid_height),
      grid_width_(grid_width),
      grid_height_(grid_height),
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
  ButtonState prev_button_state = play_pause_button_.GetState();

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake_, play_pause_button_);

    ButtonState current_button_state = play_pause_button_.GetState();
    if (current_button_state != prev_button_state)
    {
      pause_state_.RequestToggle();
      prev_button_state = current_button_state;
    }

    pause_state_.Tick();

    if (pause_state_.IsRunning())
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
      renderer.UpdateWindowTitle(score_tracker_.GetScore(), frame_count);
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
  std::vector<GridPoint> body_points;
  body_points.reserve(snake_.body.size() + 1);
  body_points.push_back({static_cast<int>(snake_.head_x), static_cast<int>(snake_.head_y)});
  for (auto const &seg : snake_.body)
  {
    body_points.push_back({seg.x, seg.y});
  }

  RandomCoordFn random_x = [this](int) { return random_w_(engine_); };
  RandomCoordFn random_y = [this](int) { return random_h_(engine_); };

  GridPoint selected{};
  food_valid_ = SelectFoodPosition(selected, static_cast<int>(grid_width_),
                                   static_cast<int>(grid_height_), body_points,
                                   random_x, random_y, kMaxFoodPlacementAttempts);
  if (food_valid_)
  {
    food_.x = selected.x;
    food_.y = selected.y;
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
  if (food_valid_ && food_.x == new_x && food_.y == new_y)
  {
    score_tracker_.AddPoint();
    PlaceFood();
    // Grow snake and increase speed.
    snake_.GrowBody();
    snake_.speed += 0.005;
  }

  if (!food_valid_)
  {
    // No legal cell remains for food: the snake has filled the board.
    snake_.alive = false;
  }
}

int Game::GetScore() const { return score_tracker_.GetScore(); }
int Game::GetSize() const { return snake_.size; }