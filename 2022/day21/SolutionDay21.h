//
// Created by Augustin Grigorov on 20/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY21_H
#define AOC2022_SOLUTIONDAY21_H

#include <fstream>

class SolutionDay21 {
public:
    explicit SolutionDay21(std::ifstream input);

    int64_t solve1();

    int64_t solve2();
private:
    int64_t puzzlePart1;
};


#endif //AOC2022_SOLUTIONDAY21_H
