#ifndef COLLISION_H
#define COLLISION_H

#include <vector>

struct GridPoint
{
    int x;
    int y;
};

bool CheckSelfCollisionLinear(GridPoint head, const std::vector<GridPoint> &body);

bool CheckFoodCollision(GridPoint head, GridPoint food);

bool CheckWallCollision(GridPoint head, int grid_width, int grid_height);

#endif
