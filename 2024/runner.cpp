//
// Created by Augustin Grigorov on 02/12/2022.
//
#include "../cpputil/ReadFileInput.h"
#include "day1/SolutionDay1.h"
#include "day2/SolutionDay2.h"
#include <iostream>


template<typename Solution>
void printResults(Solution &solution, int day) {
    std::cout << "Day " << day << " part 1: " << solution.solve1() << std::endl;
    std::cout << "Day " << day << " part 2: " << solution.solve2() << std::endl;
}

int main() {
    SolutionDay1 day1(ReadFileInput::parseFile("day1/input"));
    printResults(day1, 1);
    SolutionDay2 day2(ReadFileInput::parseFile("day2/input"));
    printResults(day2, 2);
    return 0;
}