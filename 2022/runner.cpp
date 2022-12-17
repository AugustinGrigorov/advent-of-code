//
// Created by Augustin Grigorov on 02/12/2022.
//
#include "util/Util.h"
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
#include "day12/SolutionDay12.h"
#include "day13/SolutionDay13.h"
#include "day14/SolutionDay14.h"
#include "day15/SolutionDay15.h"
#include "day16/SolutionDay16.h"
#include "day17/SolutionDay17.h"
#include <iostream>


template<typename Solution>
void printResults(Solution &solution, int day) {
    std::cout << "Day " << day << " part 1: " << solution.solve1() << std::endl;
    std::cout << "Day " << day << " part 2: " << solution.solve2() << std::endl;
}

int main() {
    SolutionDay1 day1(Util::parseFile("day1/input"));
    printResults(day1, 1);
    SolutionDay2 day2(Util::parseFile("day2/input"));
    printResults(day2, 2);
    SolutionDay3 day3(Util::parseFile("day3/input"));
    printResults(day3, 3);
    SolutionDay4 day4(Util::parseFile("day4/input"));
    printResults(day4, 4);
    SolutionDay5 day5(Util::parseFile("day5/input"));
    printResults(day5, 5);
    SolutionDay6 day6(Util::parseFile("day6/input"));
    printResults(day6, 6);
    SolutionDay7 day7(Util::parseFile("day7/input"));
    printResults(day7, 7);
    SolutionDay8 day8(Util::parseFile("day8/input"));
    printResults(day8, 8);
    SolutionDay9 day9(Util::parseFile("day9/input"));
    printResults(day9, 9);
    SolutionDay10 day10(Util::parseFile("day10/input"));
    printResults(day10, 10);
//    SolutionDay11 day11(Util::parseFile("day11/input"));
//    printResults(day11, 11);
//    SolutionDay12 day12(Util::parseFile("day12/input"));
//    printResults(day12, 12);
    SolutionDay13 day13(Util::parseFile("day13/input"));
    printResults(day13, 13);
//    SolutionDay14 day14(Util::parseFile("day14/input"));
//    printResults(day14, 14);
//    SolutionDay15 day15(Util::parseFile("day15/input"));
//    printResults(day15, 15);
    SolutionDay16 day16(Util::parseFile("day16/input"));
    printResults(day16, 16);
    SolutionDay17 day17(Util::parseFile("day17/input"));
    printResults(day17, 17);
    return 0;
}