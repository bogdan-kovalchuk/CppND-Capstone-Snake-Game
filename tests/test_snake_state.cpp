#include "test_helpers.h"
#include "snake_state.h"

void test_make_snapshot()
{
    SnakeSnapshot s = MakeSnapshot({5, 5}, 3, true, 0, 1);
    ASSERT_EQ(s.head.x, 5);
    ASSERT_EQ(s.head.y, 5);
    ASSERT_EQ(s.size, 3);
    ASSERT_TRUE(s.alive);
    ASSERT_EQ(s.direction, 0);
    ASSERT_EQ(s.pending_growth, 1);
}

void test_snapshots_equal()
{
    SnakeSnapshot a = MakeSnapshot({5, 5}, 3, true, 0, 1);
    SnakeSnapshot b = MakeSnapshot({5, 5}, 3, true, 0, 1);
    ASSERT_TRUE(SnapshotsEqual(a, b));
}

void test_snapshots_not_equal_head()
{
    SnakeSnapshot a = MakeSnapshot({5, 5}, 3, true, 0, 1);
    SnakeSnapshot b = MakeSnapshot({6, 5}, 3, true, 0, 1);
    ASSERT_FALSE(SnapshotsEqual(a, b));
}

void test_snapshots_not_equal_size()
{
    SnakeSnapshot a = MakeSnapshot({5, 5}, 3, true, 0, 1);
    SnakeSnapshot b = MakeSnapshot({5, 5}, 4, true, 0, 1);
    ASSERT_FALSE(SnapshotsEqual(a, b));
}

void test_snapshots_not_equal_alive()
{
    SnakeSnapshot a = MakeSnapshot({5, 5}, 3, true, 0, 1);
    SnakeSnapshot b = MakeSnapshot({5, 5}, 3, false, 0, 1);
    ASSERT_FALSE(SnapshotsEqual(a, b));
}

void test_snapshot_consistent_valid()
{
    SnakeSnapshot s = MakeSnapshot({5, 5}, 3, true, 0, 1);
    ASSERT_TRUE(IsSnapshotConsistent(s));
}

void test_snapshot_consistent_dead_no_growth()
{
    SnakeSnapshot s = MakeSnapshot({5, 5}, 3, false, 0, 0);
    ASSERT_TRUE(IsSnapshotConsistent(s));
}

void test_snapshot_inconsistent_zero_size()
{
    SnakeSnapshot s = MakeSnapshot({5, 5}, 0, true, 0, 0);
    ASSERT_FALSE(IsSnapshotConsistent(s));
}

void test_snapshot_inconsistent_negative_growth()
{
    SnakeSnapshot s = MakeSnapshot({5, 5}, 3, true, 0, -1);
    ASSERT_FALSE(IsSnapshotConsistent(s));
}

void test_snapshot_inconsistent_dead_with_growth()
{
    SnakeSnapshot s = MakeSnapshot({5, 5}, 3, false, 0, 2);
    ASSERT_FALSE(IsSnapshotConsistent(s));
}

void test_count_body_segments_empty()
{
    std::vector<GridPoint> body = {};
    ASSERT_EQ(CountBodySegments(body), 0);
}

void test_count_body_segments_nonempty()
{
    std::vector<GridPoint> body = {{1, 1}, {2, 2}, {3, 3}};
    ASSERT_EQ(CountBodySegments(body), 3);
}

void test_snapshot_consistent_minimum_size()
{
    SnakeSnapshot s = MakeSnapshot({0, 0}, 1, true, 0, 0);
    ASSERT_TRUE(IsSnapshotConsistent(s));
}

int main()
{
    test_make_snapshot();
    test_snapshots_equal();
    test_snapshots_not_equal_head();
    test_snapshots_not_equal_size();
    test_snapshots_not_equal_alive();
    test_snapshot_consistent_valid();
    test_snapshot_consistent_dead_no_growth();
    test_snapshot_inconsistent_zero_size();
    test_snapshot_inconsistent_negative_growth();
    test_snapshot_inconsistent_dead_with_growth();
    test_count_body_segments_empty();
    test_count_body_segments_nonempty();
    test_snapshot_consistent_minimum_size();
    return test_summary();
}
