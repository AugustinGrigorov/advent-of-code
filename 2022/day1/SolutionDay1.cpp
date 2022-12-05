//
// Created by Augustin Grigorov on 01/12/2022.
//

#include "SolutionDay1.h"
#include <string>

SolutionDay1::SolutionDay1(std::ifstream input) {
    int current = 0;
    for (std::string line; getline(input, line);) {
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

int SolutionDay1::solve1() {
    return caloriesPerElf[0];
}

int SolutionDay1::solve2() {
    return caloriesPerElf[0] + caloriesPerElf[1] + caloriesPerElf[2];
}
