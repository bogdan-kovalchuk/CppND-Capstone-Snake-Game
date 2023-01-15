#include "update_guard.h"

UpdateGuard::UpdateGuard()
    : alive_(true), paused_(true), pending_(false)
{
}

void UpdateGuard::SetAlive(bool alive)
{
    alive_ = alive;
    if (!alive_)
    {
        pending_ = false;
    }
}

void UpdateGuard::SetPaused(bool paused)
{
    paused_ = paused;
    if (paused_)
    {
        pending_ = false;
    }
}

void UpdateGuard::RequestUpdate()
{
    if (alive_ && !paused_)
    {
        pending_ = true;
    }
}

bool UpdateGuard::ShouldUpdate() const
{
    return alive_ && !paused_ && pending_;
}

void UpdateGuard::ClearPending()
{
    pending_ = false;
}

void UpdateGuard::Reset()
{
    alive_ = true;
    paused_ = true;
    pending_ = false;
}

bool UpdateGuard::IsAlive() const
{
    return alive_;
}

bool UpdateGuard::IsPaused() const
{
    return paused_;
}

bool UpdateGuard::HasPending() const
{
    return pending_;
}
