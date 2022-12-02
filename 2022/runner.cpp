//
// Created by Augustin Grigorov on 02/12/2022.
//
#include "./day1/SolutionDay1.h"
#include "./day2/SolutionDay2.h"
#include <iostream>

int main() {
    SolutionDay1 day1;
    std::cout << "Day 1 part 1: " << day1.solve1() << std::endl;
    std::cout << "Day 1 part 2: " << day1.solve2() << std::endl;
    SolutionDay2 day2;
    std::cout << "Day 2 part 1: " << day2.solve1() << std::endl;
    std::cout << "Day 2 part 2: " << day2.solve2() << std::endl;
    return 0;
}