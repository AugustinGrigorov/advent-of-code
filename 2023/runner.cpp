#include "util/ReadFileInput.h"
#include "day1/SolutionDay1.h"
#include "day2/SolutionDay2.h"
#include "day3/SolutionDay3.h"
#include "day4/SolutionDay4.h"
#include "day5/SolutionDay5.h"
#include "day6/SolutionDay6.h"
#include "day7/SolutionDay7.h"
#include "day8/SolutionDay8.h"
#include "day9/SolutionDay9.h"
#include "day10/SolutionDay10.h"
#include "day11/SolutionDay11.h"
#include <iostream>

template <typename Solution>
void printResults(Solution &solution, int day)
{
    std::cout << "Day " << day << " part 1: " << solution.solve1() << std::endl;
    std::cout << "Day " << day << " part 2: " << solution.solve2() << std::endl;
}

int main()
{
//    SolutionDay1 day1(ReadFileInput::parseFile("day1/input"));
//    printResults(day1, 1);
//    SolutionDay2 day2(ReadFileInput::parseFile("day2/input"));
//    printResults(day2, 2);
//    SolutionDay3 day3(ReadFileInput::parseFile("day3/input"));
//    printResults(day3, 3);
//    SolutionDay4 day4(ReadFileInput::parseFile("day4/input"));
//    printResults(day4, 4);
//    SolutionDay5 day5(ReadFileInput::parseFile("day5/input"));
//    printResults(day5, 5);
//    SolutionDay6 day6(ReadFileInput::parseFile("day6/input"));
//    printResults(day6, 6);
//    SolutionDay7 day7(ReadFileInput::parseFile("day7/input"));
//    printResults(day7, 7);
//    SolutionDay8 day8(ReadFileInput::parseFile("day8/input"));
//    printResults(day8, 8);
//    SolutionDay9 day9(ReadFileInput::parseFile("day9/input"));
//    printResults(day9, 9);
//    SolutionDay10 day10(ReadFileInput::parseFile("day10/input"));
//    printResults(day10, 10);
    SolutionDay11 day11(ReadFileInput::parseFile("day11/input"));
    printResults(day11, 11);
    return 0;
}