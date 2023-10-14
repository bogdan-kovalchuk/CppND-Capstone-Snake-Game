#include "test_helpers.h"
#include "game_outcome.h"
#include <cstring>

void test_playing_when_alive_and_not_paused()
{
    ASSERT_TRUE(EvaluateOutcome(true, false) == GameOutcome::kPlaying);
}

void test_game_over_when_dead()
{
    ASSERT_TRUE(EvaluateOutcome(false, false) == GameOutcome::kGameOver);
    ASSERT_TRUE(EvaluateOutcome(false, true) == GameOutcome::kGameOver);
}

void test_paused_when_alive_and_paused()
{
    ASSERT_TRUE(EvaluateOutcome(true, true) == GameOutcome::kPaused);
}

void test_terminal_state_only_game_over()
{
    ASSERT_FALSE(IsTerminalState(GameOutcome::kPlaying));
    ASSERT_TRUE(IsTerminalState(GameOutcome::kGameOver));
    ASSERT_FALSE(IsTerminalState(GameOutcome::kPaused));
}

void test_outcome_to_string()
{
    ASSERT_TRUE(std::strcmp(OutcomeToString(GameOutcome::kPlaying), "Playing") == 0);
    ASSERT_TRUE(std::strcmp(OutcomeToString(GameOutcome::kGameOver), "GameOver") == 0);
    ASSERT_TRUE(std::strcmp(OutcomeToString(GameOutcome::kPaused), "Paused") == 0);
}

void test_dead_overrides_paused()
{
    GameOutcome outcome = EvaluateOutcome(false, true);
    ASSERT_TRUE(IsTerminalState(outcome));
}

int main()
{
    test_playing_when_alive_and_not_paused();
    test_game_over_when_dead();
    test_paused_when_alive_and_paused();
    test_terminal_state_only_game_over();
    test_outcome_to_string();
    test_dead_overrides_paused();
    return test_summary();
}
