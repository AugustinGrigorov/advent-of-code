#ifndef AOC2023_SOLUTIONDAY11_H
#define AOC2023_SOLUTIONDAY11_H

#include <fstream>

class SolutionDay11
{
public:
    explicit SolutionDay11(std::ifstream input);

    long solve1() const;

    long solve2() const;
private:
    long partOneSum = 0;
    long partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY11_H
