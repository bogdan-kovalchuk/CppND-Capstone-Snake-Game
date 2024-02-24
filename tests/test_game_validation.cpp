#include "test_helpers.h"
#include "game_validation.h"

void test_valid_state()
{
    std::vector<GridPoint> body = {{4, 5}, {3, 5}};
    GameValidation v = ValidateGameState({5, 5}, {8, 8}, body, 10, 10);
    ASSERT_TRUE(v.grid_valid);
    ASSERT_TRUE(v.snake_on_grid);
    ASSERT_TRUE(v.food_on_grid);
    ASSERT_TRUE(v.no_self_collision);
    ASSERT_TRUE(IsGameStateValid(v));
    ASSERT_EQ(CountValidationFailures(v), 0);
}

void test_invalid_grid()
{
    std::vector<GridPoint> body = {};
    GameValidation v = ValidateGameState({0, 0}, {0, 0}, body, 0, 0);
    ASSERT_FALSE(v.grid_valid);
    ASSERT_FALSE(v.snake_on_grid);
    ASSERT_FALSE(v.food_on_grid);
    ASSERT_FALSE(IsGameStateValid(v));
}

void test_snake_off_grid()
{
    std::vector<GridPoint> body = {};
    GameValidation v = ValidateGameState({-1, 5}, {5, 5}, body, 10, 10);
    ASSERT_TRUE(v.grid_valid);
    ASSERT_FALSE(v.snake_on_grid);
    ASSERT_TRUE(v.food_on_grid);
    ASSERT_FALSE(IsGameStateValid(v));
}

void test_food_off_grid()
{
    std::vector<GridPoint> body = {};
    GameValidation v = ValidateGameState({5, 5}, {10, 5}, body, 10, 10);
    ASSERT_TRUE(v.grid_valid);
    ASSERT_TRUE(v.snake_on_grid);
    ASSERT_FALSE(v.food_on_grid);
    ASSERT_FALSE(IsGameStateValid(v));
}

void test_self_collision_detected()
{
    std::vector<GridPoint> body = {{5, 5}, {4, 5}};
    GameValidation v = ValidateGameState({5, 5}, {8, 8}, body, 10, 10);
    ASSERT_FALSE(v.no_self_collision);
    ASSERT_FALSE(IsGameStateValid(v));
}

void test_count_failures_multiple()
{
    std::vector<GridPoint> body = {{-1, 0}};
    GameValidation v = ValidateGameState({-1, 0}, {-1, 0}, body, 0, 0);
    ASSERT_TRUE(CountValidationFailures(v) >= 2);
}

void test_count_failures_zero_for_valid()
{
    std::vector<GridPoint> body = {{4, 5}};
    GameValidation v = ValidateGameState({5, 5}, {8, 8}, body, 10, 10);
    ASSERT_EQ(CountValidationFailures(v), 0);
}

void test_negative_grid_dimensions()
{
    std::vector<GridPoint> body = {};
    GameValidation v = ValidateGameState({0, 0}, {0, 0}, body, -5, 10);
    ASSERT_FALSE(v.grid_valid);
    ASSERT_FALSE(IsGameStateValid(v));
}

int main()
{
    test_valid_state();
    test_invalid_grid();
    test_snake_off_grid();
    test_food_off_grid();
    test_self_collision_detected();
    test_count_failures_multiple();
    test_count_failures_zero_for_valid();
    test_negative_grid_dimensions();
    return test_summary();
}
