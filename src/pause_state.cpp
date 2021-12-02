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

TickGuard::TickGuard(int min_ticks_between_toggles)
    : min_ticks_(min_ticks_between_toggles), cooldown_(0)
{
}

void TickGuard::RequestToggle()
{
    if (cooldown_ <= 0)
    {
        machine_.Toggle();
        cooldown_ = min_ticks_;
    }
}

void TickGuard::Tick()
{
    if (cooldown_ > 0)
    {
        cooldown_--;
    }
}

PauseState TickGuard::GetState() const
{
    return machine_.GetState();
}

bool TickGuard::IsRunning() const
{
    return machine_.IsRunning();
}

bool TickGuard::IsPaused() const
{
    return machine_.IsPaused();
}

int TickGuard::GetCooldown() const
{
    return cooldown_;
}
