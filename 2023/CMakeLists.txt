cmake_minimum_required(VERSION 3.23)
project(AOC2023)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_compile_definitions(_GLIBCXX_DEBUG)

add_executable(AOC2023
        util/ReadFileInput.h
        util/ReadFileInput.cpp
        day1/SolutionDay1.h
        day1/SolutionDay1.cpp
        day2/SolutionDay2.h
        day2/SolutionDay2.cpp
        day3/SolutionDay3.h
        day3/SolutionDay3.cpp
        day4/SolutionDay4.h
        day4/SolutionDay4.cpp
        day5/SolutionDay5.h
        day5/SolutionDay5.cpp
        day6/SolutionDay6.h
        day6/SolutionDay6.cpp
        runner.cpp)
