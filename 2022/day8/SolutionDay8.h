//
// Created by Augustin Grigorov on 08/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY8_H
#define AOC2022_SOLUTIONDAY8_H

#include <fstream>
#include <vector>

class SolutionDay8 {
public:
    explicit SolutionDay8(std::ifstream input);

    int solve1();

    int solve2();
private:
    int numberOfVisibleTrees = 0;
    int biggestScenicScore = 0;
};


#endif //AOC2022_SOLUTIONDAY8_H
