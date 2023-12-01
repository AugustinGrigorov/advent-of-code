#ifndef AOC2023_SOLUTIONDAY1_H
#define AOC2023_SOLUTIONDAY1_H

#include <fstream>

class SolutionDay1
{
public:
    explicit SolutionDay1(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY1_H
