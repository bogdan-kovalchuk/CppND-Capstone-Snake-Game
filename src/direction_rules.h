#ifndef DIRECTION_RULES_H
#define DIRECTION_RULES_H

enum class Dir
{
    kUp = 0,
    kDown,
    kLeft,
    kRight
};

bool IsOpposite(Dir a, Dir b);
bool IsValidDirectionChange(Dir current, Dir requested, int snake_size);
Dir GetOpposite(Dir d);

#endif
