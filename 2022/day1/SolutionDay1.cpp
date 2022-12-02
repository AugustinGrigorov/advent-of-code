//
// Created by Augustin Grigorov on 01/12/2022.
//

#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "SolutionDay1.h"

int SolutionDay1::solve1() {
    return caloriesPerElf[0];
}

int SolutionDay1::solve2() {
    return caloriesPerElf[0] + caloriesPerElf[1] + caloriesPerElf[2];
}

SolutionDay1::SolutionDay1() {
    std::string line;
    std::ifstream input;
    input.open("day1/input");
    if(!input.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    int current = 0;
    while(getline(input, line)) {
        if (!line.empty()) {
            int calories = std::stoi(line);
            current += calories;
        } else {
            caloriesPerElf.push_back(current);
            current = 0;
        }
    }
    std::sort(caloriesPerElf.begin(), caloriesPerElf.end(), std::greater<>());
}
