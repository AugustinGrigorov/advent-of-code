//
// Created by Augustin Grigorov on 20/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY20_H
#define AOC2022_SOLUTIONDAY20_H

#include <fstream>

class SolutionDay20 {
public:
    explicit SolutionDay20(std::ifstream input);

    int64_t solve1();

    int64_t solve2();
private:
    int64_t sumOfCoordinates1 = 0;
    int64_t sumOfCoordinates2 = 0;
};


#endif //AOC2022_SOLUTIONDAY20_H
