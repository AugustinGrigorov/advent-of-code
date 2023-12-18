#ifndef AOC2023_SOLUTIONDAY13_H
#define AOC2023_SOLUTIONDAY13_H

#include <fstream>

class SolutionDay13
{
public:
    explicit SolutionDay13(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY4_H
