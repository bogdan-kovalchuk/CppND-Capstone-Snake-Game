#ifndef GROWTH_TRACKER_H
#define GROWTH_TRACKER_H

class GrowthTracker
{
public:
    explicit GrowthTracker(int initial_pending = 0);

    void AddGrowth(int amount = 1);
    bool ConsumeGrowth();
    int GetPending() const;
    bool HasPending() const;
    void Reset();

private:
    int pending_;
};

#endif
