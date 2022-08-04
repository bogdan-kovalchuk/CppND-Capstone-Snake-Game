#ifndef FOOD_SAFETY_H
#define FOOD_SAFETY_H

#include "collision.h"
#include <vector>

bool IsFoodOnGrid(GridPoint food, int grid_width, int grid_height);

bool IsFoodClearOfSnake(GridPoint food, const std::vector<GridPoint> &snake_body);

bool IsFoodSafe(GridPoint food, int grid_width, int grid_height,
               const std::vector<GridPoint> &snake_body);

int CountUnsafePositions(int grid_width, int grid_height,
                         const std::vector<GridPoint> &snake_body);

bool FindFirstSafePosition(GridPoint &out, int grid_width, int grid_height,
                           const std::vector<GridPoint> &snake_body);

#endif
