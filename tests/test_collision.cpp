#include "test_helpers.h"
#include "collision.h"

void test_self_collision_no_body()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {};
    ASSERT_FALSE(CheckSelfCollisionLinear(head, body));
}

void test_self_collision_single_segment_no_hit()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{3, 3}};
    ASSERT_FALSE(CheckSelfCollisionLinear(head, body));
}

void test_self_collision_single_segment_hit()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{5, 5}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
}

void test_self_collision_multiple_segments()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{3, 3}, {4, 4}, {5, 5}, {6, 6}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
}

void test_self_collision_multiple_segments_no_hit()
{
    GridPoint head{5, 5};
    std::vector<GridPoint> body = {{1, 1}, {2, 2}, {3, 3}, {4, 4}};
    ASSERT_FALSE(CheckSelfCollisionLinear(head, body));
}

void test_self_collision_head_at_tail()
{
    GridPoint head{0, 0};
    std::vector<GridPoint> body = {{1, 0}, {2, 0}, {0, 0}};
    ASSERT_TRUE(CheckSelfCollisionLinear(head, body));
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

int main()
{
    test_self_collision_no_body();
    test_self_collision_single_segment_no_hit();
    test_self_collision_single_segment_hit();
    test_self_collision_multiple_segments();
    test_self_collision_multiple_segments_no_hit();
    test_self_collision_head_at_tail();
    test_food_collision_hit();
    test_food_collision_miss();
    test_wall_collision_inside();
    test_wall_collision_at_origin();
    test_wall_collision_at_boundary();
    test_wall_collision_past_right();
    test_wall_collision_past_bottom();
    test_wall_collision_negative();
    return test_summary();
}
