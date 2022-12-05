//
// Created by Augustin Grigorov on 01/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY1_H
#define AOC2022_SOLUTIONDAY1_H

#include <vector>
#include <fstream>

class SolutionDay1 {
public:
    explicit SolutionDay1(std::ifstream input);

    int solve1();

    int solve2();

private:
    std::vector<int> caloriesPerElf = {};
};


#endif //AOC2022_SOLUTIONDAY1_H
