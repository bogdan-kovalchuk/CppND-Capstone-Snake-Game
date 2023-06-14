#ifndef GAME_LIFECYCLE_H
#define GAME_LIFECYCLE_H

#include "collision.h"
#include "snake_state.h"

GridPoint ComputeInitialHead(int grid_width, int grid_height);

SnakeSnapshot ComputeResetSnapshot(int grid_width, int grid_height);

bool IsResetSnapshotValid(const SnakeSnapshot &snapshot, int grid_width, int grid_height);

#endif
