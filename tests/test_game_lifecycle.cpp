#include "test_helpers.h"
#include "button_state.h"
#include "game_lifecycle.h"

void test_initial_head_center_even_grid()
{
    GridPoint head = ComputeInitialHead(10, 10);
    ASSERT_EQ(head.x, 5);
    ASSERT_EQ(head.y, 5);
}

void test_initial_head_center_odd_grid()
{
    GridPoint head = ComputeInitialHead(7, 7);
    ASSERT_EQ(head.x, 3);
    ASSERT_EQ(head.y, 3);
}

void test_initial_head_rectangular_grid()
{
    GridPoint head = ComputeInitialHead(32, 16);
    ASSERT_EQ(head.x, 16);
    ASSERT_EQ(head.y, 8);
}

void test_initial_head_minimum_grid()
{
    GridPoint head = ComputeInitialHead(1, 1);
    ASSERT_EQ(head.x, 0);
    ASSERT_EQ(head.y, 0);
}

void test_reset_snapshot_consistent()
{
    SnakeSnapshot s = ComputeResetSnapshot(32, 32);
    ASSERT_TRUE(IsSnapshotConsistent(s));
    ASSERT_EQ(s.size, 1);
    ASSERT_TRUE(s.alive);
    ASSERT_EQ(s.pending_growth, 0);
    ASSERT_EQ(s.head.x, 16);
    ASSERT_EQ(s.head.y, 16);
}

void test_reset_snapshot_valid_various_grids()
{
    ASSERT_TRUE(IsResetSnapshotValid(ComputeResetSnapshot(10, 10), 10, 10));
    ASSERT_TRUE(IsResetSnapshotValid(ComputeResetSnapshot(1, 1), 1, 1));
    ASSERT_TRUE(IsResetSnapshotValid(ComputeResetSnapshot(21, 9), 21, 9));
}

void test_reset_snapshot_invalid_for_zero_grid()
{
    SnakeSnapshot s = ComputeResetSnapshot(0, 0);
    ASSERT_FALSE(IsResetSnapshotValid(s, 0, 0));
}

void test_reset_snapshot_invalid_for_negative_grid()
{
    SnakeSnapshot s = ComputeResetSnapshot(-5, 10);
    ASSERT_FALSE(IsResetSnapshotValid(s, -5, 10));
}

void test_repeated_reset_calls_are_deterministic()
{
    SnakeSnapshot a = ComputeResetSnapshot(20, 15);
    SnakeSnapshot b = ComputeResetSnapshot(20, 15);
    ASSERT_TRUE(SnapshotsEqual(a, b));
}

void test_restart_resets_button_state()
{
    ButtonStateModel button_state;
    ASSERT_TRUE(button_state.GetState() == NORMAL);

    button_state.ChangeState();
    ASSERT_TRUE(button_state.GetState() == PRESSED);

    button_state.Reset();
    ASSERT_TRUE(button_state.GetState() == NORMAL);
}

int main()
{
    test_initial_head_center_even_grid();
    test_initial_head_center_odd_grid();
    test_initial_head_rectangular_grid();
    test_initial_head_minimum_grid();
    test_reset_snapshot_consistent();
    test_reset_snapshot_valid_various_grids();
    test_reset_snapshot_invalid_for_zero_grid();
    test_reset_snapshot_invalid_for_negative_grid();
    test_repeated_reset_calls_are_deterministic();
    test_restart_resets_button_state();
    return test_summary();
}
