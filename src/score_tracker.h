#ifndef SCORE_TRACKER_H
#define SCORE_TRACKER_H

class ScoreTracker
{
public:
    ScoreTracker();

    void AddPoint(int amount = 1);
    void Reset();
    int GetScore() const;
    int GetHighScore() const;
    bool IsNewHighScore() const;

private:
    int score_;
    int high_score_;
    bool new_high_;
};

#endif
