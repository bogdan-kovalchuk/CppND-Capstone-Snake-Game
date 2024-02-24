#include "game_validation.h"

GameValidation ValidateGameState(GridPoint head, GridPoint food,
                                const std::vector<GridPoint> &body,
                                int grid_width, int grid_height)
{
    GameValidation v;
    v.grid_valid = IsValidGrid(grid_width, grid_height);
    v.snake_on_grid = v.grid_valid && IsOnGrid(head, grid_width, grid_height);
    v.food_on_grid = v.grid_valid && IsOnGrid(food, grid_width, grid_height);
    v.no_self_collision = !CheckSelfCollisionLinear(head, body);
    return v;
}

bool IsGameStateValid(const GameValidation &v)
{
    return v.grid_valid && v.snake_on_grid && v.food_on_grid && v.no_self_collision;
}

int CountValidationFailures(const GameValidation &v)
{
    int count = 0;
    if (!v.grid_valid) count++;
    if (!v.snake_on_grid) count++;
    if (!v.food_on_grid) count++;
    if (!v.no_self_collision) count++;
    return count;
}
