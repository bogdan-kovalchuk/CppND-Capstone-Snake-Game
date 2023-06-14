#include "game_lifecycle.h"

GridPoint ComputeInitialHead(int grid_width, int grid_height)
{
    return GridPoint{grid_width / 2, grid_height / 2};
}

SnakeSnapshot ComputeResetSnapshot(int grid_width, int grid_height)
{
    GridPoint head = ComputeInitialHead(grid_width, grid_height);
    return MakeSnapshot(head, 1, true, 0, 0);
}

bool IsResetSnapshotValid(const SnakeSnapshot &snapshot, int grid_width, int grid_height)
{
    if (!IsSnapshotConsistent(snapshot))
    {
        return false;
    }
    return IsOnGrid(snapshot.head, grid_width, grid_height) &&
           snapshot.size == 1 && snapshot.alive && snapshot.pending_growth == 0;
}
