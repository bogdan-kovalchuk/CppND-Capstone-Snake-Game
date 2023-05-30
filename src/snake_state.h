#ifndef SNAKE_STATE_H
#define SNAKE_STATE_H

#include "collision.h"
#include <vector>

struct SnakeSnapshot
{
    GridPoint head;
    int size;
    bool alive;
    int direction;
    int pending_growth;
};

SnakeSnapshot MakeSnapshot(GridPoint head, int size, bool alive,
                           int direction, int pending_growth);

bool SnapshotsEqual(const SnakeSnapshot &a, const SnakeSnapshot &b);

bool IsSnapshotConsistent(const SnakeSnapshot &s);

int CountBodySegments(const std::vector<GridPoint> &body);

#endif
