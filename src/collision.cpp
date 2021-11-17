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

bool CheckSelfCollisionSet(GridPoint head, const std::vector<GridPoint> &body)
{
    std::unordered_set<GridPoint, GridPointHash> occupied(body.begin(), body.end());
    return occupied.count(head) > 0;
}

bool CheckFoodCollision(GridPoint head, GridPoint food)
{
    return head.x == food.x && head.y == food.y;
}

bool CheckWallCollision(GridPoint head, int grid_width, int grid_height)
{
    if (!IsValidGrid(grid_width, grid_height))
    {
        return true;
    }
    return head.x < 0 || head.x >= grid_width ||
           head.y < 0 || head.y >= grid_height;
}

bool IsValidGrid(int grid_width, int grid_height)
{
    return grid_width > 0 && grid_height > 0;
}

bool IsOnGrid(GridPoint p, int grid_width, int grid_height)
{
    if (!IsValidGrid(grid_width, grid_height))
    {
        return false;
    }
    return p.x >= 0 && p.x < grid_width &&
           p.y >= 0 && p.y < grid_height;
}
