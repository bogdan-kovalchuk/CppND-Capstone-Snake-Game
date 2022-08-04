#include "test_helpers.h"
#include "food_safety.h"

void test_food_on_grid_valid()
{
    ASSERT_TRUE(IsFoodOnGrid({0, 0}, 10, 10));
    ASSERT_TRUE(IsFoodOnGrid({5, 5}, 10, 10));
    ASSERT_TRUE(IsFoodOnGrid({9, 9}, 10, 10));
}

void test_food_on_grid_invalid()
{
    ASSERT_FALSE(IsFoodOnGrid({-1, 0}, 10, 10));
    ASSERT_FALSE(IsFoodOnGrid({10, 5}, 10, 10));
    ASSERT_FALSE(IsFoodOnGrid({5, -1}, 10, 10));
    ASSERT_FALSE(IsFoodOnGrid({5, 10}, 10, 10));
}

void test_food_on_grid_invalid_dimensions()
{
    ASSERT_FALSE(IsFoodOnGrid({0, 0}, 0, 0));
    ASSERT_FALSE(IsFoodOnGrid({0, 0}, -1, 10));
}

void test_food_clear_of_snake_empty_body()
{
    std::vector<GridPoint> body = {};
    ASSERT_TRUE(IsFoodClearOfSnake({5, 5}, body));
}

void test_food_clear_of_snake_no_overlap()
{
    std::vector<GridPoint> body = {{1, 1}, {2, 2}, {3, 3}};
    ASSERT_TRUE(IsFoodClearOfSnake({5, 5}, body));
}

void test_food_clear_of_snake_overlap()
{
    std::vector<GridPoint> body = {{1, 1}, {5, 5}, {3, 3}};
    ASSERT_FALSE(IsFoodClearOfSnake({5, 5}, body));
}

void test_food_safe_all_conditions_met()
{
    std::vector<GridPoint> body = {{1, 1}, {2, 2}};
    ASSERT_TRUE(IsFoodSafe({5, 5}, 10, 10, body));
}

void test_food_safe_off_grid()
{
    std::vector<GridPoint> body = {};
    ASSERT_FALSE(IsFoodSafe({-1, 5}, 10, 10, body));
}

void test_food_safe_on_snake()
{
    std::vector<GridPoint> body = {{5, 5}};
    ASSERT_FALSE(IsFoodSafe({5, 5}, 10, 10, body));
}

void test_count_unsafe_empty_body()
{
    std::vector<GridPoint> body = {};
    ASSERT_EQ(CountUnsafePositions(3, 3, body), 0);
}

void test_count_unsafe_with_body()
{
    std::vector<GridPoint> body = {{0, 0}, {1, 1}};
    ASSERT_EQ(CountUnsafePositions(3, 3, body), 2);
}

void test_count_unsafe_invalid_grid()
{
    std::vector<GridPoint> body = {};
    ASSERT_EQ(CountUnsafePositions(0, 0, body), 0);
    ASSERT_EQ(CountUnsafePositions(-1, 10, body), 0);
}

void test_count_unsafe_full_grid()
{
    std::vector<GridPoint> body = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    ASSERT_EQ(CountUnsafePositions(2, 2, body), 4);
}

int main()
{
    test_food_on_grid_valid();
    test_food_on_grid_invalid();
    test_food_on_grid_invalid_dimensions();
    test_food_clear_of_snake_empty_body();
    test_food_clear_of_snake_no_overlap();
    test_food_clear_of_snake_overlap();
    test_food_safe_all_conditions_met();
    test_food_safe_off_grid();
    test_food_safe_on_snake();
    test_count_unsafe_empty_body();
    test_count_unsafe_with_body();
    test_count_unsafe_invalid_grid();
    test_count_unsafe_full_grid();
    return test_summary();
}
