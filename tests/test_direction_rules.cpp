#include "test_helpers.h"
#include "direction_rules.h"

void test_same_direction_is_invalid()
{
    ASSERT_FALSE(IsValidDirectionChange(Dir::kUp, Dir::kUp, 5));
    ASSERT_FALSE(IsValidDirectionChange(Dir::kDown, Dir::kDown, 5));
    ASSERT_FALSE(IsValidDirectionChange(Dir::kLeft, Dir::kLeft, 5));
    ASSERT_FALSE(IsValidDirectionChange(Dir::kRight, Dir::kRight, 5));
}

void test_perpendicular_change_is_valid()
{
    ASSERT_TRUE(IsValidDirectionChange(Dir::kUp, Dir::kLeft, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kUp, Dir::kRight, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kDown, Dir::kLeft, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kDown, Dir::kRight, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kLeft, Dir::kUp, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kLeft, Dir::kDown, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kRight, Dir::kUp, 5));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kRight, Dir::kDown, 5));
}

void test_opposite_change_invalid_for_multi_segment()
{
    ASSERT_FALSE(IsValidDirectionChange(Dir::kUp, Dir::kDown, 5));
    ASSERT_FALSE(IsValidDirectionChange(Dir::kDown, Dir::kUp, 5));
    ASSERT_FALSE(IsValidDirectionChange(Dir::kLeft, Dir::kRight, 5));
    ASSERT_FALSE(IsValidDirectionChange(Dir::kRight, Dir::kLeft, 5));
}

void test_opposite_change_valid_for_single_segment()
{
    ASSERT_TRUE(IsValidDirectionChange(Dir::kUp, Dir::kDown, 1));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kDown, Dir::kUp, 1));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kLeft, Dir::kRight, 1));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kRight, Dir::kLeft, 1));
}

void test_is_opposite_symmetric()
{
    ASSERT_TRUE(IsOpposite(Dir::kUp, Dir::kDown));
    ASSERT_TRUE(IsOpposite(Dir::kDown, Dir::kUp));
    ASSERT_TRUE(IsOpposite(Dir::kLeft, Dir::kRight));
    ASSERT_TRUE(IsOpposite(Dir::kRight, Dir::kLeft));
    ASSERT_FALSE(IsOpposite(Dir::kUp, Dir::kLeft));
    ASSERT_FALSE(IsOpposite(Dir::kUp, Dir::kUp));
}

void test_get_opposite()
{
    ASSERT_TRUE(GetOpposite(Dir::kUp) == Dir::kDown);
    ASSERT_TRUE(GetOpposite(Dir::kDown) == Dir::kUp);
    ASSERT_TRUE(GetOpposite(Dir::kLeft) == Dir::kRight);
    ASSERT_TRUE(GetOpposite(Dir::kRight) == Dir::kLeft);
}

void test_opposite_change_valid_for_size_two()
{
    ASSERT_TRUE(IsValidDirectionChange(Dir::kUp, Dir::kDown, 2));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kLeft, Dir::kRight, 2));
}

void test_direction_change_zero_size()
{
    ASSERT_FALSE(IsValidDirectionChange(Dir::kUp, Dir::kDown, 0));
    ASSERT_TRUE(IsValidDirectionChange(Dir::kUp, Dir::kLeft, 0));
}

int main()
{
    test_same_direction_is_invalid();
    test_perpendicular_change_is_valid();
    test_opposite_change_invalid_for_multi_segment();
    test_opposite_change_valid_for_single_segment();
    test_is_opposite_symmetric();
    test_get_opposite();
    test_opposite_change_valid_for_size_two();
    test_direction_change_zero_size();
    return test_summary();
}
