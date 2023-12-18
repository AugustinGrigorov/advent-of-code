#ifndef AOC2023_SOLUTIONDAY17_H
#define AOC2023_SOLUTIONDAY17_H

#include <fstream>

class SolutionDay17
{
public:
    explicit SolutionDay17(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY17_H
