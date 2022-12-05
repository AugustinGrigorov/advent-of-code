//
// Created by Augustin Grigorov on 04/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY4_H
#define AOC2022_SOLUTIONDAY4_H

#include <fstream>

class SolutionDay4 {
public:
    explicit SolutionDay4(std::ifstream input);

    int solve1();

    int solve2();

private:
    int totalOverlapOccurrences = 0;
    int partialOverlapOccurrences = 0;
};


#endif //AOC2022_SOLUTIONDAY4_H
