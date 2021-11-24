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

int main()
{
    test_initial_state_is_paused();
    test_toggle_from_paused_to_running();
    test_toggle_from_running_to_paused();
    test_multiple_toggles();
    test_toggle_preserves_running_state();
    test_get_state_returns_enum();
    return test_summary();
}
