//
// Created by Augustin Grigorov on 02/12/2022.
//
#include "day1/SolutionDay1.h"
#include "day2/SolutionDay2.h"
#include "day3/SolutionDay3.h"
#include "day4/SolutionDay4.h"
#include "day5/SolutionDay5.h"
#include "util/ReadFileInput.h"
#include <iostream>


template<typename Solution>
void printResults(Solution solution, int day) {
    std::cout << "Day " << day << " part 1: " << solution.solve1() << std::endl;
    std::cout << "Day " << day << " part 2: " << solution.solve2() << std::endl;
 }

int main() {
    SolutionDay1 day1(ReadFileInput::parseFile("day1/input"));
    printResults(day1, 1);
    SolutionDay2 day2(ReadFileInput::parseFile("day2/input"));
    printResults(day2, 2);
    SolutionDay3 day3(ReadFileInput::parseFile("day3/input"));
    printResults(day3, 3);
    SolutionDay4 day4(ReadFileInput::parseFile("day4/input"));
    printResults(day4, 4);
    SolutionDay5 day5(ReadFileInput::parseFile("day5/input"));
    printResults(day5, 5);
    return 0;
}