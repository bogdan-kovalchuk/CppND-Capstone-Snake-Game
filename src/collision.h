#ifndef COLLISION_H
#define COLLISION_H

#include <functional>
#include <unordered_set>
#include <vector>

struct GridPoint
{
    int x;
    int y;
};

struct GridPointHash
{
    std::size_t operator()(const GridPoint &p) const
    {
        auto hx = std::hash<int>{}(p.x);
        auto hy = std::hash<int>{}(p.y);
        return hx ^ (hy * 2654435761u);
    }
};

inline bool operator==(const GridPoint &a, const GridPoint &b)
{
    return a.x == b.x && a.y == b.y;
}

bool CheckSelfCollisionLinear(GridPoint head, const std::vector<GridPoint> &body);

bool CheckSelfCollisionSet(GridPoint head, const std::vector<GridPoint> &body);

bool CheckFoodCollision(GridPoint head, GridPoint food);

bool CheckWallCollision(GridPoint head, int grid_width, int grid_height);

#endif
