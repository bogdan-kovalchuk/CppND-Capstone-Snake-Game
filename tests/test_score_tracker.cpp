#include "test_helpers.h"
#include "score_tracker.h"

void test_initial_score_zero()
{
    ScoreTracker st;
    ASSERT_EQ(st.GetScore(), 0);
    ASSERT_EQ(st.GetHighScore(), 0);
    ASSERT_FALSE(st.IsNewHighScore());
}

void test_add_single_point()
{
    ScoreTracker st;
    st.AddPoint();
    ASSERT_EQ(st.GetScore(), 1);
    ASSERT_EQ(st.GetHighScore(), 1);
    ASSERT_TRUE(st.IsNewHighScore());
}

void test_add_multiple_points()
{
    ScoreTracker st;
    st.AddPoint(3);
    ASSERT_EQ(st.GetScore(), 3);
    ASSERT_EQ(st.GetHighScore(), 3);
    st.AddPoint(2);
    ASSERT_EQ(st.GetScore(), 5);
    ASSERT_EQ(st.GetHighScore(), 5);
}

void test_add_zero_no_effect()
{
    ScoreTracker st;
    st.AddPoint(0);
    ASSERT_EQ(st.GetScore(), 0);
}

void test_add_negative_no_effect()
{
    ScoreTracker st;
    st.AddPoint(5);
    st.AddPoint(-3);
    ASSERT_EQ(st.GetScore(), 5);
}

void test_high_score_persists_after_reset()
{
    ScoreTracker st;
    st.AddPoint(10);
    ASSERT_EQ(st.GetHighScore(), 10);
    st.Reset();
    ASSERT_EQ(st.GetScore(), 0);
    ASSERT_EQ(st.GetHighScore(), 10);
}

void test_new_high_score_flag()
{
    ScoreTracker st;
    st.AddPoint(5);
    ASSERT_TRUE(st.IsNewHighScore());
    st.Reset();
    st.AddPoint(3);
    ASSERT_FALSE(st.IsNewHighScore());
}

void test_new_high_score_on_tie()
{
    ScoreTracker st;
    st.AddPoint(5);
    st.Reset();
    st.AddPoint(5);
    ASSERT_FALSE(st.IsNewHighScore());
}

void test_reset_clears_new_high_flag()
{
    ScoreTracker st;
    st.AddPoint(5);
    ASSERT_TRUE(st.IsNewHighScore());
    st.Reset();
    ASSERT_FALSE(st.IsNewHighScore());
}

int main()
{
    test_initial_score_zero();
    test_add_single_point();
    test_add_multiple_points();
    test_add_zero_no_effect();
    test_add_negative_no_effect();
    test_high_score_persists_after_reset();
    test_new_high_score_flag();
    test_new_high_score_on_tie();
    test_reset_clears_new_high_flag();
    return test_summary();
}
