# Collision Detection

## Overview

The collision module (`src/collision.h`, `src/collision.cpp`) provides
SDL-independent point-geometry checks used by the snake game loop. A
`GridPoint{int x, int y}` replaces `SDL_Point` so that the logic compiles
and runs in focused unit tests without linking SDL.

## Functions

| Function | Purpose |
|---|---|
| `CheckSelfCollisionLinear` | O(n) scan of body segments for head overlap |
| `CheckSelfCollisionSet` | O(n) build + O(1) lookup via `unordered_set` |
| `CheckFoodCollision` | Point equality between head and food |
| `CheckWallCollision` | Bounds check against grid dimensions |
| `IsValidGrid` | Reject non-positive grid dimensions |
| `IsOnGrid` | Inverse of wall collision with validation |

## Complexity

| Approach | Time | Space | Notes |
|---|---|---|---|
| Linear scan | O(n) | O(1) | Cache-friendly; best for small bodies |
| Hash set | O(n) build, O(1) query | O(n) | Better when querying same body repeatedly |

For the typical snake game (body < 100 segments) the linear scan is
faster in practice due to lower constant factors and no allocation.
The set-based approach becomes advantageous if the same body is
queried many times per frame (e.g., food placement validation).

## Design Decisions

- **No SDL dependency**: `GridPoint` mirrors `SDL_Point` layout so
  conversion is a trivial member-wise copy.
- **Free functions**: Collision checks are pure functions with no
  hidden state, making them straightforward to test and reason about.
- **Defensive grid validation**: `CheckWallCollision` returns `true`
  (collision) for non-positive grid dimensions, preventing undefined
  behavior from silently passing invalid coordinates.
