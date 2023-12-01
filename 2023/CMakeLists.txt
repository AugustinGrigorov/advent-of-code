cmake_minimum_required(VERSION 3.23)
project(AOC2023)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

add_executable(AOC2023
        util/ReadFileInput.h
        util/ReadFileInput.cpp
        day1/SolutionDay1.h
        day1/SolutionDay1.cpp
        runner.cpp)
