//
// Created by Augustin Grigorov on 02/12/2022.
//
#include "day1/SolutionDay1.h"
#include "day2/SolutionDay2.h"
#include "day3/SolutionDay3.h"
#include "day4/SolutionDay4.h"
#include "day5/SolutionDay5.h"
#include <iostream>

int main() {
    SolutionDay1 day1;
    std::cout << "Day 1 part 1: " << day1.solve1() << std::endl;
    std::cout << "Day 1 part 2: " << day1.solve2() << std::endl;
    SolutionDay2 day2;
    std::cout << "Day 2 part 1: " << day2.solve1() << std::endl;
    std::cout << "Day 2 part 2: " << day2.solve2() << std::endl;
    SolutionDay3 day3;
    std::cout << "Day 3 part 1: " << day3.solve1() << std::endl;
    std::cout << "Day 3 part 2: " << day3.solve2() << std::endl;
    SolutionDay4 day4;
    std::cout << "Day 4 part 1: " << day4.solve1() << std::endl;
    std::cout << "Day 4 part 2: " << day4.solve2() << std::endl;
    SolutionDay5 day5;
    std::cout << "Day 5 part 1: " << day5.solve1() << std::endl;
    std::cout << "Day 5 part 2: " << day5.solve2() << std::endl;
    return 0;
}