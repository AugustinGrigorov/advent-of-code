#include "util/ReadFileInput.h"
#include "day1/SolutionDay1.h"
#include <iostream>

template <typename Solution>
void printResults(Solution &solution, int day)
{
    std::cout << "Day " << day << " part 1: " << solution.solve1() << std::endl;
    std::cout << "Day " << day << " part 2: " << solution.solve2() << std::endl;
}

int main()
{
    SolutionDay1 day1(ReadFileInput::parseFile("day1/input"));
    printResults(day1, 1);
    return 0;
}