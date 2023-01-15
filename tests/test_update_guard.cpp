#include "test_helpers.h"
#include "update_guard.h"

void test_initial_state()
{
    UpdateGuard ug;
    ASSERT_TRUE(ug.IsAlive());
    ASSERT_TRUE(ug.IsPaused());
    ASSERT_FALSE(ug.HasPending());
    ASSERT_FALSE(ug.ShouldUpdate());
}

void test_request_update_while_paused()
{
    UpdateGuard ug;
    ug.RequestUpdate();
    ASSERT_FALSE(ug.HasPending());
    ASSERT_FALSE(ug.ShouldUpdate());
}

void test_request_update_when_alive_and_running()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ASSERT_TRUE(ug.HasPending());
    ASSERT_TRUE(ug.ShouldUpdate());
}

void test_request_update_when_dead()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.SetAlive(false);
    ug.RequestUpdate();
    ASSERT_FALSE(ug.HasPending());
    ASSERT_FALSE(ug.ShouldUpdate());
}

void test_clear_pending()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ASSERT_TRUE(ug.ShouldUpdate());
    ug.ClearPending();
    ASSERT_FALSE(ug.ShouldUpdate());
    ASSERT_FALSE(ug.HasPending());
}

void test_death_clears_pending()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ASSERT_TRUE(ug.HasPending());
    ug.SetAlive(false);
    ASSERT_FALSE(ug.HasPending());
    ASSERT_FALSE(ug.ShouldUpdate());
}

void test_pause_blocks_update()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ASSERT_TRUE(ug.ShouldUpdate());
    ug.SetPaused(true);
    ASSERT_FALSE(ug.ShouldUpdate());
}

void test_reset_restores_initial()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.SetAlive(false);
    ug.RequestUpdate();
    ug.Reset();
    ASSERT_TRUE(ug.IsAlive());
    ASSERT_TRUE(ug.IsPaused());
    ASSERT_FALSE(ug.HasPending());
}

void test_resume_after_pause()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ug.ClearPending();
    ug.SetPaused(true);
    ug.SetPaused(false);
    ug.RequestUpdate();
    ASSERT_TRUE(ug.ShouldUpdate());
}

void test_multiple_requests_while_running()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ug.RequestUpdate();
    ug.RequestUpdate();
    ASSERT_TRUE(ug.HasPending());
    ASSERT_TRUE(ug.ShouldUpdate());
    ug.ClearPending();
    ASSERT_FALSE(ug.HasPending());
}

void test_pause_clears_pending()
{
    UpdateGuard ug;
    ug.SetPaused(false);
    ug.RequestUpdate();
    ASSERT_TRUE(ug.HasPending());
    ug.SetPaused(true);
    ASSERT_FALSE(ug.HasPending());
    ASSERT_FALSE(ug.ShouldUpdate());
}

int main()
{
    test_initial_state();
    test_request_update_while_paused();
    test_request_update_when_alive_and_running();
    test_request_update_when_dead();
    test_clear_pending();
    test_death_clears_pending();
    test_pause_blocks_update();
    test_reset_restores_initial();
    test_resume_after_pause();
    test_multiple_requests_while_running();
    test_pause_clears_pending();
    return test_summary();
}
