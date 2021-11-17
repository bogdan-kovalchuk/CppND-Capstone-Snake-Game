#include "test_helpers.h"
#include "collision.h"

void test_self_collision_no_body()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {};
    ASSERT_FALSE(CheckSelfCollisionLinear(head, body));
    ASSERT_FALSE(CheckSelfCollisionSet(head, body));
}

void test_self_collision_single_segment_no_hit()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{3, 3}};
    ASSERT_FALSE(CheckSelfCollisionLinear(head, body));
    ASSERT_FALSE(CheckSelfCollisionSet(head, body));
}

void test_self_collision_single_segment_hit()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{5, 5}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
    ASSERT_TRUE(CheckSelfCollisionSet(head, body));
}

void test_self_collision_multiple_segments()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{3, 3}, {4, 4}, {5, 5}, {6, 6}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
    ASSERT_TRUE(CheckSelfCollisionSet(head, body));
}

void test_self_collision_multiple_segments_no_hit()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    ASSERT_FALSE(CheckSelfCollisionLinear(head, body));
    ASSERT_FALSE(CheckSelfCollisionSet(head, body));
}

void test_self_collision_head_at_tail()
{
    GridPoint head{0, 0};
    std::vector<GridPoint> body = {{1, 0}, {2, 0}, {0, 0}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
    ASSERT_TRUE(CheckSelfCollisionSet(head, body));
}

void test_comparison_both_agree_on_empty()
{
    GridPoint head{0, 0};
    std::vector<GridPoint> body = {};
    ASSERT_EQ(CheckSelfCollisionLinear(head, body),
              CheckSelfCollisionSet(head, body));
}

void test_comparison_both_agree_on_large_body()
{
    std::vector<GridPoint> body;
    for (int i = 0; i < 100; ++i)
    {
        body.push_back({i, i});
    }
    GridPoint head_miss{50, 51};
    GridPoint head_hit{50, 50};
    ASSERT_EQ(CheckSelfCollisionLinear(head_miss, body),
              CheckSelfCollisionSet(head_miss, body));
    ASSERT_EQ(CheckSelfCollisionLinear(head_hit, body),
              CheckSelfCollisionSet(head_hit, body));
}

void test_comparison_both_agree_on_duplicate_segments()
{
    GridPoint head{3, 3};
    std::vector<GridPoint> body = {{1, 1}, {3, 3}, {3, 3}, {2, 2}};
    ASSERT_EQ(CheckSelfCollisionLinear(head, body),
              CheckSelfCollisionSet(head, body));
}

void test_food_collision_hit()
{
    GridPoint head{3, 7};
    GridPoint food{3, 7};
    ASSERT_TRUE(CheckFoodCollision(head, food));
}

void test_food_collision_miss()
{
    GridPoint head{3, 7};
    GridPoint food{4, 7};
    ASSERT_FALSE(CheckFoodCollision(head, food));
}

void test_wall_collision_inside()
{
    GridPoint head{5, 5};
    ASSERT_FALSE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_at_origin()
{
    GridPoint head{0, 0};
    ASSERT_FALSE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_at_boundary()
{
    GridPoint head{9, 9};
    ASSERT_FALSE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_past_right()
{
    GridPoint head{10, 5};
    ASSERT_TRUE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_past_bottom()
{
    GridPoint head{5, 10};
    ASSERT_TRUE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_negative()
{
    GridPoint head{-1, 5};
    ASSERT_TRUE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_negative_y()
{
    GridPoint head{5, -1};
    ASSERT_TRUE(CheckWallCollision(head, 10, 10));
}

void test_wall_collision_zero_grid()
{
    GridPoint head{0, 0};
    ASSERT_TRUE(CheckWallCollision(head, 0, 0));
}

void test_wall_collision_negative_grid()
{
    GridPoint head{0, 0};
    ASSERT_TRUE(CheckWallCollision(head, -5, 10));
}

void test_is_valid_grid_positive()
{
    ASSERT_TRUE(IsValidGrid(10, 10));
    ASSERT_TRUE(IsValidGrid(1, 1));
}

void test_is_valid_grid_zero()
{
    ASSERT_FALSE(IsValidGrid(0, 10));
    ASSERT_FALSE(IsValidGrid(10, 0));
    ASSERT_FALSE(IsValidGrid(0, 0));
}

void test_is_valid_grid_negative()
{
    ASSERT_FALSE(IsValidGrid(-1, 10));
    ASSERT_FALSE(IsValidGrid(10, -1));
}

void test_is_on_grid_valid_inside()
{
    ASSERT_TRUE(IsOnGrid({5, 5}, 10, 10));
    ASSERT_TRUE(IsOnGrid({0, 0}, 10, 10));
    ASSERT_TRUE(IsOnGrid({9, 9}, 10, 10));
}

void test_is_on_grid_valid_outside()
{
    ASSERT_FALSE(IsOnGrid({10, 5}, 10, 10));
    ASSERT_FALSE(IsOnGrid({5, 10}, 10, 10));
    ASSERT_FALSE(IsOnGrid({-1, 5}, 10, 10));
}

void test_is_on_grid_invalid_dimensions()
{
    ASSERT_FALSE(IsOnGrid({0, 0}, 0, 0));
    ASSERT_FALSE(IsOnGrid({0, 0}, -1, 10));
}

void test_self_collision_large_coordinates()
{
    GridPoint head{1000, 2000};
    std::vector<GridPoint> body = {{1000, 2000}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
    ASSERT_TRUE(CheckSelfCollisionSet(head, body));
}

void test_food_collision_negative_coords()
{
    GridPoint head{-3, -7};
    GridPoint food{-3, -7};
    ASSERT_TRUE(CheckFoodCollision(head, food));
}

int main()
{
    test_self_collision_no_body();
    test_self_collision_single_segment_no_hit();
    test_self_collision_single_segment_hit();
    test_self_collision_multiple_segments();
    test_self_collision_multiple_segments_no_hit();
    test_self_collision_head_at_tail();
    test_comparison_both_agree_on_empty();
    test_comparison_both_agree_on_large_body();
    test_comparison_both_agree_on_duplicate_segments();
    test_food_collision_hit();
    test_food_collision_miss();
    test_wall_collision_inside();
    test_wall_collision_at_origin();
    test_wall_collision_at_boundary();
    test_wall_collision_past_right();
    test_wall_collision_past_bottom();
    test_wall_collision_negative();
    test_wall_collision_negative_y();
    test_wall_collision_zero_grid();
    test_wall_collision_negative_grid();
    test_is_valid_grid_positive();
    test_is_valid_grid_zero();
    test_is_valid_grid_negative();
    test_is_on_grid_valid_inside();
    test_is_on_grid_valid_outside();
    test_is_on_grid_invalid_dimensions();
    test_self_collision_large_coordinates();
    test_food_collision_negative_coords();
    return test_summary();
}
