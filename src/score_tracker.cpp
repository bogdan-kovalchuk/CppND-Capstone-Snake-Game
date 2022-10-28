#include "score_tracker.h"

ScoreTracker::ScoreTracker()
    : score_(0), high_score_(0), new_high_(false)
{
}

void ScoreTracker::AddPoint(int amount)
{
    if (amount <= 0)
    {
        return;
    }
    score_ += amount;
    if (score_ > high_score_)
    {
        high_score_ = score_;
        new_high_ = true;
    }
    else
    {
        new_high_ = false;
    }
}

void ScoreTracker::Reset()
{
    score_ = 0;
    new_high_ = false;
}

int ScoreTracker::GetScore() const
{
    return score_;
}

int ScoreTracker::GetHighScore() const
{
    return high_score_;
}

bool ScoreTracker::IsNewHighScore() const
{
    return new_high_;
}
