//
// Created by Augustin Grigorov on 17/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY17_H
#define AOC2022_SOLUTIONDAY17_H

#include <fstream>


class SolutionDay17 {
public:
    explicit SolutionDay17(std::ifstream input);

    int64_t solve1();

    int64_t solve2();
private:
    int64_t highestPointPart1 = 0;
    int64_t highestPointPart2 = 0;
};


#endif //AOC2022_SOLUTIONDAY17_H
