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

enable_testing()
add_test(NAME CollisionTests COMMAND test_collision)
add_test(NAME PauseStateTests COMMAND test_pause_state)
add_test(NAME DirectionRulesTests COMMAND test_direction_rules)
add_test(NAME GrowthTrackerTests COMMAND test_growth_tracker)
add_test(NAME FoodSafetyTests COMMAND test_food_safety)
