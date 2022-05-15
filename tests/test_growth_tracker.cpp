#include "test_helpers.h"
#include "growth_tracker.h"

void test_initial_pending_zero()
{
    GrowthTracker gt;
    ASSERT_EQ(gt.GetPending(), 0);
    ASSERT_FALSE(gt.HasPending());
}

void test_initial_pending_positive()
{
    GrowthTracker gt(3);
    ASSERT_EQ(gt.GetPending(), 3);
    ASSERT_TRUE(gt.HasPending());
}

void test_initial_pending_negative_clamped()
{
    GrowthTracker gt(-5);
    ASSERT_EQ(gt.GetPending(), 0);
    ASSERT_FALSE(gt.HasPending());
}

void test_add_growth_single()
{
    GrowthTracker gt;
    gt.AddGrowth();
    ASSERT_EQ(gt.GetPending(), 1);
    ASSERT_TRUE(gt.HasPending());
}

void test_add_growth_multiple()
{
    GrowthTracker gt;
    gt.AddGrowth(3);
    ASSERT_EQ(gt.GetPending(), 3);
    gt.AddGrowth(2);
    ASSERT_EQ(gt.GetPending(), 5);
}

void test_add_growth_zero_no_effect()
{
    GrowthTracker gt;
    gt.AddGrowth(0);
    ASSERT_EQ(gt.GetPending(), 0);
}

void test_add_growth_negative_no_effect()
{
    GrowthTracker gt(2);
    gt.AddGrowth(-1);
    ASSERT_EQ(gt.GetPending(), 2);
}

void test_consume_growth_success()
{
    GrowthTracker gt(2);
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_EQ(gt.GetPending(), 1);
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_EQ(gt.GetPending(), 0);
}

void test_consume_growth_empty()
{
    GrowthTracker gt;
    ASSERT_FALSE(gt.ConsumeGrowth());
    ASSERT_EQ(gt.GetPending(), 0);
}

void test_consume_growth_does_not_go_negative()
{
    GrowthTracker gt(1);
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_FALSE(gt.ConsumeGrowth());
    ASSERT_EQ(gt.GetPending(), 0);
}

void test_reset_clears_pending()
{
    GrowthTracker gt(5);
    gt.Reset();
    ASSERT_EQ(gt.GetPending(), 0);
    ASSERT_FALSE(gt.HasPending());
}

void test_add_then_consume_cycle()
{
    GrowthTracker gt;
    gt.AddGrowth(3);
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_FALSE(gt.ConsumeGrowth());
    gt.AddGrowth(1);
    ASSERT_TRUE(gt.ConsumeGrowth());
    ASSERT_FALSE(gt.ConsumeGrowth());
}

int main()
{
    test_initial_pending_zero();
    test_initial_pending_positive();
    test_initial_pending_negative_clamped();
    test_add_growth_single();
    test_add_growth_multiple();
    test_add_growth_zero_no_effect();
    test_add_growth_negative_no_effect();
    test_consume_growth_success();
    test_consume_growth_empty();
    test_consume_growth_does_not_go_negative();
    test_reset_clears_pending();
    test_add_then_consume_cycle();
    return test_summary();
}
