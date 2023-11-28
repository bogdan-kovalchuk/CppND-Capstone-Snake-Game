#include "test_helpers.h"
#include "collision.h"
#include "direction_rules.h"
#include "food_placer.h"
#include "game_lifecycle.h"
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

struct GameResult
{
    GridPoint head;
    int size;
    int score;
    std::size_t body_size;
};

GameResult RunScriptedGame(GridPoint start_head)
{
    GridPoint head = start_head;
    std::vector<GridPoint> body;
    int size = 1;
    bool alive = true;
    Dir direction = Dir::kRight;
    GrowthTracker growth;
    ScoreTracker score;
    GridPoint food{start_head.x + 1, start_head.y};

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

    return GameResult{head, size, score.GetScore(), body.size()};
}

} // namespace

void test_scripted_run_tracks_score_growth_and_snapshot_invariants()
{
    // The script eats the food and reverses direction (allowed at size <= 2);
    // the reversal safely retraces the single trailing segment.
    GameResult result = RunScriptedGame(GridPoint{3, 3});
    ASSERT_EQ(result.head.x, 3);
    ASSERT_EQ(result.head.y, 3);
    ASSERT_EQ(result.size, 2);
    ASSERT_EQ(result.score, 1);
    ASSERT_EQ(static_cast<int>(result.body_size), 1);
}

void test_reset_replays_scripted_game_deterministically()
{
    constexpr int grid_width = 8;
    constexpr int grid_height = 6;
    SnakeSnapshot reset = ComputeResetSnapshot(grid_width, grid_height);
    ASSERT_TRUE(IsResetSnapshotValid(reset, grid_width, grid_height));

    GameResult first_run = RunScriptedGame(reset.head);
    reset = ComputeResetSnapshot(grid_width, grid_height);
    GameResult second_run = RunScriptedGame(reset.head);

    ASSERT_EQ(first_run.head.x, 4);
    ASSERT_EQ(first_run.head.y, 3);
    ASSERT_EQ(first_run.size, 2);
    ASSERT_EQ(first_run.score, 1);
    ASSERT_EQ(static_cast<int>(first_run.body_size), 1);
    ASSERT_EQ(second_run.head.x, first_run.head.x);
    ASSERT_EQ(second_run.head.y, first_run.head.y);
    ASSERT_EQ(second_run.size, first_run.size);
    ASSERT_EQ(second_run.score, first_run.score);
    ASSERT_EQ(static_cast<int>(second_run.body_size),
              static_cast<int>(first_run.body_size));
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
    test_reset_replays_scripted_game_deterministically();
    test_collision_leads_to_terminal_outcome();
    test_food_placer_after_scripted_eat_avoids_body();
    return test_summary();
}
