#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "button.h"

class Controller
{
public:
    void HandleInput(bool &running, bool &restart_requested, Snake &snake,
                     Button &play_pause_button) const;

private:
    void HandleMouseEvent(const SDL_Event &e, Button &play_pause_button) const;
    void HandleKeyboardEvent(const SDL_Event &e, Snake &snake, bool &restart_requested) const;
    void ChangeDirection(Snake &snake, Snake::Direction input) const;
};

#endif