#include "direction_rules.h"

bool IsOpposite(Dir a, Dir b)
{
    return (a == Dir::kUp && b == Dir::kDown) ||
           (a == Dir::kDown && b == Dir::kUp) ||
           (a == Dir::kLeft && b == Dir::kRight) ||
           (a == Dir::kRight && b == Dir::kLeft);
}

Dir GetOpposite(Dir d)
{
    switch (d)
    {
    case Dir::kUp:    return Dir::kDown;
    case Dir::kDown:  return Dir::kUp;
    case Dir::kLeft:  return Dir::kRight;
    case Dir::kRight: return Dir::kLeft;
    }
    return d;
}

bool IsValidDirectionChange(Dir current, Dir requested, int snake_size)
{
    if (current == requested)
    {
        return false;
    }
    if (IsOpposite(current, requested) && (snake_size < 1 || snake_size > 2))
    {
        return false;
    }
    return true;
}
