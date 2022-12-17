//
// Created by Augustin Grigorov on 15/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY15_H
#define AOC2022_SOLUTIONDAY15_H

#include <fstream>

class SolutionDay15 {
public:
    explicit SolutionDay15(std::ifstream input);

    int solve1();

    int solve2();
private:
    int lowerBoundX = INT_MAX;
    int upperBoundX = INT_MIN;
    int spotsWhereBeaconCannotBe = 0;
};


#endif //AOC2022_SOLUTIONDAY15_H
