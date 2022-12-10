//
// Created by Augustin Grigorov on 10/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY10_H
#define AOC2022_SOLUTIONDAY10_H

#include <fstream>
#include <string>

class SolutionDay10 {
public:
    explicit SolutionDay10(std::ifstream input);

    int solve1();

    std::string solve2();
private:
    int cycles = 1;
    int regX = 1;
    int signalStrength = 0;
    std::string output = "\n";
};


#endif //AOC2022_SOLUTIONDAY10_H
