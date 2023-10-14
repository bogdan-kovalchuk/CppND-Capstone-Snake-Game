#include "game_outcome.h"

GameOutcome EvaluateOutcome(bool alive, bool paused)
{
    if (!alive)
    {
        return GameOutcome::kGameOver;
    }
    if (paused)
    {
        return GameOutcome::kPaused;
    }
    return GameOutcome::kPlaying;
}

bool IsTerminalState(GameOutcome outcome)
{
    return outcome == GameOutcome::kGameOver;
}

const char *OutcomeToString(GameOutcome outcome)
{
    switch (outcome)
    {
    case GameOutcome::kPlaying:
        return "Playing";
    case GameOutcome::kGameOver:
        return "GameOver";
    case GameOutcome::kPaused:
        return "Paused";
    }
    return "Unknown";
}
