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

    SDL_Point button_position = play_pause_button.GetPosition();
    ButtonDimensions button_dimentions = play_pause_button.GetButtonDimensions();

    float button_center_x = button_position.x + button_dimentions.w / 2.0;
    float button_center_y = button_position.y + button_dimentions.h / 2.0;

    // Distance from center of button to mouse position
    float dist = sqrt(pow((button_center_x - x), 2) + pow((button_center_y - y), 2));

    // Assume that button is round (special case of this project)
    // Check if distance between center of the button and mouse position is
    // less than radius (w/2 or h/2) so that check if mouse is in button
    if (dist <= button_dimentions.w / 2.0)
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