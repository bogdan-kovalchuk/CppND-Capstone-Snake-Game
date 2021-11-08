#include <iostream>
#include <SDL2/SDL.h>

#include "controller.h"
#include "snake.h"
#include "button.h"

void Controller::ChangeDirection(Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const
{
  if (snake.direction != opposite || snake.size == 1)
    snake.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Snake &snake, Button &play_pause_button) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      running = false;
    }
    else
    {
      HandleMouseEvent(e, play_pause_button);
      HandleKeyboardEvent(e, snake);
    }
  }
}

void Controller::HandleMouseEvent(const SDL_Event &e, Button &play_pause_button) const
{
  // Check if mouse event happened
  if (e.type == SDL_MOUSEBUTTONDOWN)
  {
    // Get mouse position
    int x, y;
    SDL_GetMouseState(&x, &y);

    // Check if mouse is in button
    bool inside = true;

    // Mouse is left of the button
    // if (x < mPosition.x)
    // {
    //   inside = false;
    // }
    // // Mouse is right of the button
    // else if (x > mPosition.x + BUTTON_WIDTH)
    // {
    //   inside = false;
    // }
    // // Mouse above the button
    // else if (y < mPosition.y)
    // {
    //   inside = false;
    // }
    // // Mouse below the button
    // else if (y > mPosition.y + BUTTON_HEIGHT)
    // {
    //   inside = false;
    // }

    // Mouse is inside button
    if (inside)
    {
      play_pause_button.ChangeState();
    }
  }
}

void Controller::HandleKeyboardEvent(const SDL_Event &e, Snake &snake) const
{
  // Check if keyboard event happened
  if (e.type == SDL_KEYDOWN)
  {
    switch (e.key.keysym.sym)
    {
    case SDLK_UP:
      ChangeDirection(snake, Snake::Direction::kUp,
                      Snake::Direction::kDown);
      break;

    case SDLK_DOWN:
      ChangeDirection(snake, Snake::Direction::kDown,
                      Snake::Direction::kUp);
      break;

    case SDLK_LEFT:
      ChangeDirection(snake, Snake::Direction::kLeft,
                      Snake::Direction::kRight);
      break;

    case SDLK_RIGHT:
      ChangeDirection(snake, Snake::Direction::kRight,
                      Snake::Direction::kLeft);
      break;
    }
  }
}