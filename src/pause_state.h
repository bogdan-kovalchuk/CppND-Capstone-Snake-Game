#ifndef PAUSE_STATE_H
#define PAUSE_STATE_H

enum class PauseState
{
    kRunning,
    kPaused
};

class PauseStateMachine
{
public:
    PauseStateMachine();

    void Toggle();

    PauseState GetState() const;
    bool IsRunning() const;
    bool IsPaused() const;

private:
    PauseState state_;
};

#endif
