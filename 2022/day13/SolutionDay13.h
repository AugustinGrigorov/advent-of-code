//
// Created by Augustin Grigorov on 13/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY13_H
#define AOC2022_SOLUTIONDAY13_H

#include <fstream>

class SolutionDay13 {
public:
    explicit SolutionDay13(std::ifstream input);

    int solve1();

    int solve2();
private:
    int packetsInTheRightOrder = 0;
    int dividerProduct = 1;
};


#endif //AOC2022_SOLUTIONDAY13_H
