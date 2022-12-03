cmake_minimum_required(VERSION 3.23)
project(AOC2022)

set(CMAKE_CXX_STANDARD 23)

add_executable(AOC2022 day1/SolutionDay1.h
        day1/SolutionDay1.cpp
        day2/SolutionDay2.h
        day2/SolutionDay2.cpp
        day3/SolutionDay3.h
        day3/SolutionDay3.cpp
        runner.cpp)
