#include "collision.h"

bool CheckSelfCollisionLinear(GridPoint head, const std::vector<GridPoint> &body)
{
    for (const auto &segment : body)
    {
        if (head.x == segment.x && head.y == segment.y)
        {
            return true;
        }
    }
    return false;
}

bool CheckFoodCollision(GridPoint head, GridPoint food)
{
    return head.x == food.x && head.y == food.y;
}

bool CheckWallCollision(GridPoint head, int grid_width, int grid_height)
{
    return head.x < 0 || head.x >= grid_width ||
           head.y < 0 || head.y >= grid_height;
}
