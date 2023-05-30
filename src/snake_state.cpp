#include "snake_state.h"

SnakeSnapshot MakeSnapshot(GridPoint head, int size, bool alive,
                           int direction, int pending_growth)
{
    return SnakeSnapshot{head, size, alive, direction, pending_growth};
}

bool SnapshotsEqual(const SnakeSnapshot &a, const SnakeSnapshot &b)
{
    return a.head.x == b.head.x &&
           a.head.y == b.head.y &&
           a.size == b.size &&
           a.alive == b.alive &&
           a.direction == b.direction &&
           a.pending_growth == b.pending_growth;
}

bool IsSnapshotConsistent(const SnakeSnapshot &s)
{
    if (s.size < 1)
    {
        return false;
    }
    if (s.pending_growth < 0)
    {
        return false;
    }
    if (!s.alive && s.pending_growth > 0)
    {
        return false;
    }
    return true;
}

int CountBodySegments(const std::vector<GridPoint> &body)
{
    return static_cast<int>(body.size());
}
