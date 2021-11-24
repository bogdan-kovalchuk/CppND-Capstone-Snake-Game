#include "pause_state.h"

PauseStateMachine::PauseStateMachine()
    : state_(PauseState::kPaused)
{
}

void PauseStateMachine::Toggle()
{
    if (state_ == PauseState::kRunning)
    {
        state_ = PauseState::kPaused;
    }
    else
    {
        state_ = PauseState::kRunning;
    }
}

PauseState PauseStateMachine::GetState() const
{
    return state_;
}

bool PauseStateMachine::IsRunning() const
{
    return state_ == PauseState::kRunning;
}

bool PauseStateMachine::IsPaused() const
{
    return state_ == PauseState::kPaused;
}
