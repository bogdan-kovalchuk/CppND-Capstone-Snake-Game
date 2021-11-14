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

enable_testing()
add_test(NAME CollisionTests COMMAND test_collision)
