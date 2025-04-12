cmake_minimum_required(VERSION 3.23)
project(AOC2024)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

set(SOLVED_PUZZLES 4)
# Add any skipped puzzles to this list
set(SKIPPED_PUZZLES)

add_compile_definitions(_GLIBCXX_DEBUG)

add_executable(AOC2024
        ../cpputil/ReadFileInput.h
        ../cpputil/ReadFileInput.cpp
        runner.cpp)

# This will automatically add all needed files per solved problem
set(PUZZLE_INDEX 1)
while(PUZZLE_INDEX LESS_EQUAL SOLVED_PUZZLES)
        if(NOT PUZZLE_INDEX IN_LIST SKIPPED_PUZZLES)
                target_sources(AOC2024 PRIVATE
                        day${PUZZLE_INDEX}/SolutionDay${PUZZLE_INDEX}.h
                        day${PUZZLE_INDEX}/SolutionDay${PUZZLE_INDEX}.cpp)
        endif()
        math(EXPR PUZZLE_INDEX "${PUZZLE_INDEX} + 1")
endwhile()
