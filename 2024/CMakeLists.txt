cmake_minimum_required(VERSION 3.23)
project(AOC2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(SOLVED_PUZZLES 4)

add_compile_definitions(_GLIBCXX_DEBUG)

add_executable(AOC2024
        ../cpputil/ReadFileInput.h
        ../cpputil/ReadFileInput.cpp
        runner.cpp)

# This will automatically add all needed files per solved problem
set(CURRENT_PUZZLE_EXECUTABLE 1)
while(CURRENT_PUZZLE_EXECUTABLE LESS_EQUAL SOLVED_PUZZLES)
        target_sources(AOC2024 PRIVATE
                day${CURRENT_PUZZLE_EXECUTABLE}/SolutionDay${CURRENT_PUZZLE_EXECUTABLE}.h
                day${CURRENT_PUZZLE_EXECUTABLE}/SolutionDay${CURRENT_PUZZLE_EXECUTABLE}.cpp)
        math(EXPR CURRENT_PUZZLE_EXECUTABLE "${CURRENT_PUZZLE_EXECUTABLE} + 1")
endwhile()
