#include "test_helpers.h"
#include "food_placer.h"

RandomCoordFn MakeSequenceFn(std::vector<int> values)
{
    return [values, i = std::size_t{0}](int bound) mutable -> int
    {
        int v = values[i % values.size()];
        i++;
        return bound > 0 ? (v % bound) : 0;
    };
}

void test_selects_first_safe_random_candidate()
{
    std::vector<GridPoint> body = {};
    RandomCoordFn rx = MakeSequenceFn({2});
    RandomCoordFn ry = MakeSequenceFn({3});
    GridPoint out{};
    ASSERT_TRUE(SelectFoodPosition(out, 10, 10, body, rx, ry, 5));
    ASSERT_EQ(out.x, 2);
    ASSERT_EQ(out.y, 3);
}

void test_skips_unsafe_candidates_until_safe()
{
    std::vector<GridPoint> body = {{0, 0}};
    RandomCoordFn rx = MakeSequenceFn({0, 4});
    RandomCoordFn ry = MakeSequenceFn({0, 4});
    GridPoint out{};
    ASSERT_TRUE(SelectFoodPosition(out, 10, 10, body, rx, ry, 5));
    ASSERT_EQ(out.x, 4);
    ASSERT_EQ(out.y, 4);
}

void test_falls_back_to_scan_when_attempts_exhausted()
{
    std::vector<GridPoint> body = {{0, 0}};
    RandomCoordFn rx = MakeSequenceFn({0});
    RandomCoordFn ry = MakeSequenceFn({0});
    GridPoint out{};
    ASSERT_TRUE(SelectFoodPosition(out, 2, 2, body, rx, ry, 3));
    ASSERT_EQ(out.x, 1);
    ASSERT_EQ(out.y, 0);
}

void test_returns_false_when_board_full()
{
    std::vector<GridPoint> body = {{0, 0}};
    RandomCoordFn rx = MakeSequenceFn({0});
    RandomCoordFn ry = MakeSequenceFn({0});
    GridPoint out{};
    ASSERT_FALSE(SelectFoodPosition(out, 1, 1, body, rx, ry, 4));
}

void test_invalid_grid_returns_false()
{
    std::vector<GridPoint> body = {};
    RandomCoordFn rx = MakeSequenceFn({0});
    RandomCoordFn ry = MakeSequenceFn({0});
    GridPoint out{};
    ASSERT_FALSE(SelectFoodPosition(out, 0, 10, body, rx, ry, 5));
    ASSERT_FALSE(SelectFoodPosition(out, 10, -1, body, rx, ry, 5));
}

void test_zero_max_attempts_uses_fallback_only()
{
    std::vector<GridPoint> body = {{0, 0}};
    RandomCoordFn rx = MakeSequenceFn({0});
    RandomCoordFn ry = MakeSequenceFn({0});
    GridPoint out{};
    ASSERT_TRUE(SelectFoodPosition(out, 3, 3, body, rx, ry, 0));
    ASSERT_EQ(out.x, 1);
    ASSERT_EQ(out.y, 0);
}

void test_deterministic_repeat_produces_same_result()
{
    std::vector<GridPoint> body = {{1, 1}};
    GridPoint out_a{};
    GridPoint out_b{};
    ASSERT_TRUE(SelectFoodPosition(out_a, 8, 8, body, MakeSequenceFn({1, 1, 3}),
                                   MakeSequenceFn({1, 1, 5}), 5));
    ASSERT_TRUE(SelectFoodPosition(out_b, 8, 8, body, MakeSequenceFn({1, 1, 3}),
                                   MakeSequenceFn({1, 1, 5}), 5));
    ASSERT_EQ(out_a.x, out_b.x);
    ASSERT_EQ(out_a.y, out_b.y);
}

int main()
{
    test_selects_first_safe_random_candidate();
    test_skips_unsafe_candidates_until_safe();
    test_falls_back_to_scan_when_attempts_exhausted();
    test_returns_false_when_board_full();
    test_invalid_grid_returns_false();
    test_zero_max_attempts_uses_fallback_only();
    test_deterministic_repeat_produces_same_result();
    return test_summary();
}
