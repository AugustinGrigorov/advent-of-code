#ifndef AOC2023_SOLUTIONDAY12_H
#define AOC2023_SOLUTIONDAY12_H

#include <fstream>

class SolutionDay12
{
public:
    explicit SolutionDay12(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY12_H
