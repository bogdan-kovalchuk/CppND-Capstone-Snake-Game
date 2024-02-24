#ifndef GAME_VALIDATION_H
#define GAME_VALIDATION_H

#include "collision.h"
#include <vector>

struct GameValidation
{
    bool grid_valid;
    bool snake_on_grid;
    bool food_on_grid;
    bool no_self_collision;
};

GameValidation ValidateGameState(GridPoint head, GridPoint food,
                                const std::vector<GridPoint> &body,
                                int grid_width, int grid_height);

bool IsGameStateValid(const GameValidation &v);

int CountValidationFailures(const GameValidation &v);

#endif
