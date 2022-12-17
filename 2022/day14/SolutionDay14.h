//
// Created by Augustin Grigorov on 14/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY14_H
#define AOC2022_SOLUTIONDAY14_H

#include <fstream>

class SolutionDay14 {
public:
    explicit SolutionDay14(std::ifstream input);

    int solve1();

    int solve2();
private:
    int lowestPoint = 0;
    int unitsOfSandInCavePart1 = 0;
    int unitsOfSandInCavePart2 = 0;
};


#endif //AOC2022_SOLUTIONDAY14_H
