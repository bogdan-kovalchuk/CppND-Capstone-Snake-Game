#include "snake.h"
#include "collision.h"
#include "game_lifecycle.h"
#include <cmath>
#include <iostream>

void Snake::Update()
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y)
  {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead()
{
  switch (direction)
  {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width_, grid_width_);
  head_y = fmod(head_y + grid_height_, grid_height_);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell)
{
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growth_.ConsumeGrowth())
  {
    // Remove the tail from the vector.
    body.erase(body.begin());
  }
  else
  {
    size++;
  }

  // Check if the snake has died.
  std::vector<GridPoint> body_points;
  body_points.reserve(body.size());
  for (const auto &seg : body)
  {
    body_points.push_back({seg.x, seg.y});
  }
  if (CheckSelfCollisionLinear({current_head_cell.x, current_head_cell.y},
                               body_points))
  {
    alive = false;
  }
}

void Snake::GrowBody() { growth_.AddGrowth(); }

void Snake::Reset()
{
  GridPoint initial = ComputeInitialHead(grid_width_, grid_height_);
  head_x = static_cast<float>(initial.x);
  head_y = static_cast<float>(initial.y);
  body.clear();
  size = 1;
  alive = true;
  direction = Direction::kUp;
  speed = kInitialSpeed;
  growth_.Reset();
}

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y)
{
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y))
  {
    return true;
  }
  for (auto const &item : body)
  {
    if (x == item.x && y == item.y)
    {
      return true;
    }
  }
  return false;
}