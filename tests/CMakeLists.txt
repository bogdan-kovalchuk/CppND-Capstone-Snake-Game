cmake_minimum_required(VERSION 3.7)
project(SnakeTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Wall -Wextra -Wpedantic)

add_executable(test_collision
    test_collision.cpp
    ../src/collision.cpp
)
target_include_directories(test_collision PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_pause_state
    test_pause_state.cpp
    ../src/pause_state.cpp
)
target_include_directories(test_pause_state PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_direction_rules
    test_direction_rules.cpp
    ../src/direction_rules.cpp
)
target_include_directories(test_direction_rules PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_growth_tracker
    test_growth_tracker.cpp
    ../src/growth_tracker.cpp
)
target_include_directories(test_growth_tracker PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_food_safety
    test_food_safety.cpp
    ../src/food_safety.cpp
    ../src/collision.cpp
)
target_include_directories(test_food_safety PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_score_tracker
    test_score_tracker.cpp
    ../src/score_tracker.cpp
)
target_include_directories(test_score_tracker PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_update_guard
    test_update_guard.cpp
    ../src/update_guard.cpp
)
target_include_directories(test_update_guard PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_snake_state
    test_snake_state.cpp
    ../src/snake_state.cpp
    ../src/collision.cpp
)
target_include_directories(test_snake_state PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_game_outcome
    test_game_outcome.cpp
    ../src/game_outcome.cpp
)
target_include_directories(test_game_outcome PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_game_validation
    test_game_validation.cpp
    ../src/game_validation.cpp
    ../src/collision.cpp
)
target_include_directories(test_game_validation PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_food_placer
    test_food_placer.cpp
    ../src/food_placer.cpp
    ../src/food_safety.cpp
    ../src/collision.cpp
)
target_include_directories(test_food_placer PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_game_lifecycle
    test_game_lifecycle.cpp
    ../src/game_lifecycle.cpp
    ../src/snake_state.cpp
    ../src/collision.cpp
)
target_include_directories(test_game_lifecycle PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_game_simulation
    test_game_simulation.cpp
    ../src/collision.cpp
    ../src/direction_rules.cpp
    ../src/food_placer.cpp
    ../src/food_safety.cpp
    ../src/game_outcome.cpp
    ../src/growth_tracker.cpp
    ../src/score_tracker.cpp
    ../src/snake_state.cpp
)
target_include_directories(test_game_simulation PRIVATE ../src ${CMAKE_CURRENT_SOURCE_DIR})

enable_testing()
add_test(NAME CollisionTests COMMAND test_collision)
add_test(NAME PauseStateTests COMMAND test_pause_state)
add_test(NAME DirectionRulesTests COMMAND test_direction_rules)
add_test(NAME GrowthTrackerTests COMMAND test_growth_tracker)
add_test(NAME FoodSafetyTests COMMAND test_food_safety)
add_test(NAME ScoreTrackerTests COMMAND test_score_tracker)
add_test(NAME UpdateGuardTests COMMAND test_update_guard)
add_test(NAME SnakeStateTests COMMAND test_snake_state)
add_test(NAME GameOutcomeTests COMMAND test_game_outcome)
add_test(NAME GameValidationTests COMMAND test_game_validation)
add_test(NAME FoodPlacerTests COMMAND test_food_placer)
add_test(NAME GameLifecycleTests COMMAND test_game_lifecycle)
add_test(NAME GameSimulationTests COMMAND test_game_simulation)
