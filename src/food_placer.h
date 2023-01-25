#ifndef FOOD_PLACER_H
#define FOOD_PLACER_H

#include "collision.h"
#include <functional>
#include <vector>

using RandomCoordFn = std::function<int(int)>;

bool SelectFoodPosition(GridPoint &out, int grid_width, int grid_height,
                        const std::vector<GridPoint> &snake_body,
                        const RandomCoordFn &random_x, const RandomCoordFn &random_y,
                        int max_random_attempts);

#endif
