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
    void Reset();

    PauseState GetState() const;
    bool IsRunning() const;
    bool IsPaused() const;

private:
    PauseState state_;
};

class TickGuard
{
public:
    explicit TickGuard(int min_ticks_between_toggles = 3);

    void RequestToggle();
    void Tick();
    void Reset();

    PauseState GetState() const;
    bool IsRunning() const;
    bool IsPaused() const;
    int GetCooldown() const;

private:
    PauseStateMachine machine_;
    int min_ticks_;
    int cooldown_;
};

#endif
