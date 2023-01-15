#ifndef UPDATE_GUARD_H
#define UPDATE_GUARD_H

class UpdateGuard
{
public:
    UpdateGuard();

    void SetAlive(bool alive);
    void SetPaused(bool paused);
    void RequestUpdate();
    bool ShouldUpdate() const;
    void ClearPending();
    void Reset();

    bool IsAlive() const;
    bool IsPaused() const;
    bool HasPending() const;

private:
    bool alive_;
    bool paused_;
    bool pending_;
};

#endif
