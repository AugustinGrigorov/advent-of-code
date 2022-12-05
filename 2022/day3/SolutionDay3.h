//
// Created by Augustin Grigorov on 03/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY3_H
#define AOC2022_SOLUTIONDAY3_H

#include <vector>
#include <fstream>

class SolutionDay3 {
public:
    explicit SolutionDay3(std::ifstream input);

    int solve1();

    int solve2();

private:
    std::vector<char> improperlyPlacedItems;
    int badgeSum = 0;
};


#endif //AOC2022_SOLUTIONDAY3_H
