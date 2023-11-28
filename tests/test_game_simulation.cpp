#include "test_helpers.h"
#include "collision.h"
#include "direction_rules.h"
#include "food_placer.h"
#include "game_outcome.h"
#include "growth_tracker.h"
#include "score_tracker.h"
#include "snake_state.h"

namespace
{

GridPoint MoveHead(GridPoint head, Dir direction)
{
    switch (direction)
    {
    case Dir::kUp:
        return GridPoint{head.x, head.y - 1};
    case Dir::kDown:
        return GridPoint{head.x, head.y + 1};
    case Dir::kLeft:
        return GridPoint{head.x - 1, head.y};
    case Dir::kRight:
        return GridPoint{head.x + 1, head.y};
    }
    return head;
}

struct ScriptStep
{
    Dir requested_direction;
    GridPoint next_food;
};

} // namespace

void test_scripted_run_tracks_score_growth_and_snapshot_invariants()
{
    GridPoint head{3, 3};
    std::vector<GridPoint> body;
    int size = 1;
    bool alive = true;
    Dir direction = Dir::kRight;
    GrowthTracker growth;
    ScoreTracker score;
    GridPoint food{4, 3};

    std::vector<ScriptStep> steps = {
        {Dir::kRight, {0, 0}},
        {Dir::kLeft, {0, 0}},
    };

    for (const auto &step : steps)
    {
        if (IsValidDirectionChange(direction, step.requested_direction, size))
        {
            direction = step.requested_direction;
        }

        GridPoint prev_head = head;
        head = MoveHead(head, direction);

        body.push_back(prev_head);
        if (!growth.ConsumeGrowth())
        {
            body.erase(body.begin());
        }
        else
        {
            size++;
        }

        ASSERT_FALSE(CheckSelfCollisionLinear(head, body));

        if (CheckFoodCollision(head, food))
        {
            score.AddPoint();
            growth.AddGrowth();
            food = step.next_food;
        }

        SnakeSnapshot snap = MakeSnapshot(head, size, alive, static_cast<int>(direction),
                                          growth.GetPending());
        ASSERT_TRUE(IsSnapshotConsistent(snap));
    }

    // First step eats the food and reverses direction (allowed at size <= 2);
    // the reversal safely retraces the single trailing segment.
    ASSERT_EQ(head.x, 3);
    ASSERT_EQ(head.y, 3);
    ASSERT_EQ(size, 2);
    ASSERT_EQ(score.GetScore(), 1);
    ASSERT_EQ(static_cast<int>(body.size()), 1);
}

void test_collision_leads_to_terminal_outcome()
{
    GridPoint head{2, 2};
    std::vector<GridPoint> body = {{1, 2}, {2, 2}, {3, 2}};

    bool collided = CheckSelfCollisionLinear(head, body);
    ASSERT_TRUE(collided);

    bool alive = !collided;
    GameOutcome outcome = EvaluateOutcome(alive, false);
    ASSERT_TRUE(outcome == GameOutcome::kGameOver);
    ASSERT_TRUE(IsTerminalState(outcome));
}

void test_food_placer_after_scripted_eat_avoids_body()
{
    GridPoint head{4, 3};
    std::vector<GridPoint> body = {};
    std::vector<GridPoint> occupied = {head};
    for (auto const &seg : body)
    {
        occupied.push_back(seg);
    }

    RandomCoordFn rx = [](int bound) { return bound > 0 ? 5 % bound : 0; };
    RandomCoordFn ry = [](int bound) { return bound > 0 ? 5 % bound : 0; };

    GridPoint placed{};
    ASSERT_TRUE(SelectFoodPosition(placed, 6, 6, occupied, rx, ry, 5));

    ASSERT_TRUE(placed.x >= 0 && placed.x < 6);
    ASSERT_TRUE(placed.y >= 0 && placed.y < 6);
    bool overlaps_snake = false;
    for (auto const &seg : occupied)
    {
        if (seg.x == placed.x && seg.y == placed.y)
        {
            overlaps_snake = true;
        }
    }
    ASSERT_FALSE(overlaps_snake);
}

int main()
{
    test_scripted_run_tracks_score_growth_and_snapshot_invariants();
    test_collision_leads_to_terminal_outcome();
    test_food_placer_after_scripted_eat_avoids_body();
    return test_summary();
}
