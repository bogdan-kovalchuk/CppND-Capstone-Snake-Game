#include "food_safety.h"

bool IsFoodOnGrid(GridPoint food, int grid_width, int grid_height)
{
    return IsOnGrid(food, grid_width, grid_height);
}

bool IsFoodClearOfSnake(GridPoint food, const std::vector<GridPoint> &snake_body)
{
    for (const auto &seg : snake_body)
    {
        if (food.x == seg.x && food.y == seg.y)
        {
            return false;
        }
    }
    return true;
}

bool IsFoodSafe(GridPoint food, int grid_width, int grid_height,
               const std::vector<GridPoint> &snake_body)
{
    if (!IsFoodOnGrid(food, grid_width, grid_height))
    {
        return false;
    }
    return IsFoodClearOfSnake(food, snake_body);
}

int CountUnsafePositions(int grid_width, int grid_height,
                         const std::vector<GridPoint> &snake_body)
{
    if (!IsValidGrid(grid_width, grid_height))
    {
        return 0;
    }
    int count = 0;
    for (int y = 0; y < grid_height; ++y)
    {
        for (int x = 0; x < grid_width; ++x)
        {
            GridPoint p{x, y};
            if (!IsFoodClearOfSnake(p, snake_body))
            {
                count++;
            }
        }
    }
    return count;
}

bool FindFirstSafePosition(GridPoint &out, int grid_width, int grid_height,
                           const std::vector<GridPoint> &snake_body)
{
    if (!IsValidGrid(grid_width, grid_height))
    {
        return false;
    }
    for (int y = 0; y < grid_height; ++y)
    {
        for (int x = 0; x < grid_width; ++x)
        {
            GridPoint p{x, y};
            if (IsFoodClearOfSnake(p, snake_body))
            {
                out = p;
                return true;
            }
        }
    }
    return false;
}
