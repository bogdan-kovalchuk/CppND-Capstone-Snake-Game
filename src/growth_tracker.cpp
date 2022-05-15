#include "growth_tracker.h"

GrowthTracker::GrowthTracker(int initial_pending)
    : pending_(initial_pending > 0 ? initial_pending : 0)
{
}

void GrowthTracker::AddGrowth(int amount)
{
    if (amount > 0)
    {
        pending_ += amount;
    }
}

bool GrowthTracker::ConsumeGrowth()
{
    if (pending_ > 0)
    {
        pending_--;
        return true;
    }
    return false;
}

int GrowthTracker::GetPending() const
{
    return pending_;
}

bool GrowthTracker::HasPending() const
{
    return pending_ > 0;
}

void GrowthTracker::Reset()
{
    pending_ = 0;
}
