#ifndef GAME_OUTCOME_H
#define GAME_OUTCOME_H

enum class GameOutcome
{
    kPlaying,
    kGameOver,
    kPaused
};

GameOutcome EvaluateOutcome(bool alive, bool paused);
bool IsTerminalState(GameOutcome outcome);
const char *OutcomeToString(GameOutcome outcome);

#endif
