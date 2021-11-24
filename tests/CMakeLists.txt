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

enable_testing()
add_test(NAME CollisionTests COMMAND test_collision)
add_test(NAME PauseStateTests COMMAND test_pause_state)
