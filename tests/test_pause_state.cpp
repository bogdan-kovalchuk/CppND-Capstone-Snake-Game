#include "test_helpers.h"
#include "pause_state.h"

void test_initial_state_is_paused()
{
    PauseStateMachine sm;
    ASSERT_TRUE(sm.IsPaused());
    ASSERT_FALSE(sm.IsRunning());
    ASSERT_EQ(static_cast<int>(sm.GetState()), static_cast<int>(PauseState::kPaused));
}

void test_toggle_from_paused_to_running()
{
    PauseStateMachine sm;
    sm.Toggle();
    ASSERT_TRUE(sm.IsRunning());
    ASSERT_FALSE(sm.IsPaused());
    ASSERT_EQ(static_cast<int>(sm.GetState()), static_cast<int>(PauseState::kRunning));
}

void test_toggle_from_running_to_paused()
{
    PauseStateMachine sm;
    sm.Toggle();
    sm.Toggle();
    ASSERT_TRUE(sm.IsPaused());
    ASSERT_FALSE(sm.IsRunning());
}

void test_multiple_toggles()
{
    PauseStateMachine sm;
    for (int i = 0; i < 10; ++i)
    {
        sm.Toggle();
        ASSERT_TRUE(sm.IsRunning());
        sm.Toggle();
        ASSERT_TRUE(sm.IsPaused());
    }
}

void test_toggle_preserves_running_state()
{
    PauseStateMachine sm;
    sm.Toggle();
    ASSERT_TRUE(sm.IsRunning());
    sm.Toggle();
    ASSERT_TRUE(sm.IsPaused());
    sm.Toggle();
    ASSERT_TRUE(sm.IsRunning());
}

void test_get_state_returns_enum()
{
    PauseStateMachine sm;
    ASSERT_EQ(static_cast<int>(sm.GetState()),
              static_cast<int>(PauseState::kPaused));
    sm.Toggle();
    ASSERT_EQ(static_cast<int>(sm.GetState()),
              static_cast<int>(PauseState::kRunning));
}

void test_tickguard_initial_paused()
{
    TickGuard tg(3);
    ASSERT_TRUE(tg.IsPaused());
    ASSERT_FALSE(tg.IsRunning());
    ASSERT_EQ(tg.GetCooldown(), 0);
}

void test_tickguard_toggle_with_cooldown()
{
    TickGuard tg(3);
    tg.RequestToggle();
    ASSERT_TRUE(tg.IsRunning());
    ASSERT_EQ(tg.GetCooldown(), 3);
    tg.RequestToggle();
    ASSERT_TRUE(tg.IsRunning());
    ASSERT_EQ(tg.GetCooldown(), 3);
}

void test_tickguard_cooldown_decrements()
{
    TickGuard tg(3);
    tg.RequestToggle();
    ASSERT_EQ(tg.GetCooldown(), 3);
    tg.Tick();
    ASSERT_EQ(tg.GetCooldown(), 2);
    tg.Tick();
    ASSERT_EQ(tg.GetCooldown(), 1);
    tg.Tick();
    ASSERT_EQ(tg.GetCooldown(), 0);
}

void test_tickguard_toggle_after_cooldown()
{
    TickGuard tg(2);
    tg.RequestToggle();
    ASSERT_TRUE(tg.IsRunning());
    tg.Tick();
    tg.Tick();
    ASSERT_EQ(tg.GetCooldown(), 0);
    tg.RequestToggle();
    ASSERT_TRUE(tg.IsPaused());
    ASSERT_EQ(tg.GetCooldown(), 2);
}

void test_tickguard_no_negative_cooldown()
{
    TickGuard tg(1);
    tg.Tick();
    tg.Tick();
    tg.Tick();
    ASSERT_EQ(tg.GetCooldown(), 0);
}

void test_tickguard_default_cooldown()
{
    TickGuard tg;
    tg.RequestToggle();
    ASSERT_EQ(tg.GetCooldown(), 3);
}

int main()
{
    test_initial_state_is_paused();
    test_toggle_from_paused_to_running();
    test_toggle_from_running_to_paused();
    test_multiple_toggles();
    test_toggle_preserves_running_state();
    test_get_state_returns_enum();
    test_tickguard_initial_paused();
    test_tickguard_toggle_with_cooldown();
    test_tickguard_cooldown_decrements();
    test_tickguard_toggle_after_cooldown();
    test_tickguard_no_negative_cooldown();
    test_tickguard_default_cooldown();
    return test_summary();
}
