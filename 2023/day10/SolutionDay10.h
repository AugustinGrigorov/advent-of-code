#ifndef AOC2023_SOLUTIONDAY10_H
#define AOC2023_SOLUTIONDAY10_H

#include <fstream>

class SolutionDay10
{
public:
    explicit SolutionDay10(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY10_H
