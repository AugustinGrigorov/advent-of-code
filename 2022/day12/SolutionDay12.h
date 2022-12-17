//
// Created by Augustin Grigorov on 12/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY12_H
#define AOC2022_SOLUTIONDAY12_H

#include <fstream>

class SolutionDay12 {
public:
    explicit SolutionDay12(std::ifstream input);

    int solve1();

    int solve2();
private:
    int shortestPathFromStart = 0;
    int shortestPathFromAnywhere = INT_MAX;
};


#endif //AOC2022_SOLUTIONDAY12_H
