#include "food_placer.h"
#include "food_safety.h"

bool SelectFoodPosition(GridPoint &out, int grid_width, int grid_height,
                        const std::vector<GridPoint> &snake_body,
                        const RandomCoordFn &random_x, const RandomCoordFn &random_y,
                        int max_random_attempts)
{
    if (!IsValidGrid(grid_width, grid_height))
    {
        return false;
    }

    for (int attempt = 0; attempt < max_random_attempts; ++attempt)
    {
        GridPoint candidate{random_x(grid_width), random_y(grid_height)};
        if (IsFoodSafe(candidate, grid_width, grid_height, snake_body))
        {
            out = candidate;
            return true;
        }
    }

    return FindFirstSafePosition(out, grid_width, grid_height, snake_body);
}
