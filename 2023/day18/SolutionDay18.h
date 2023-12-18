#ifndef AOC2023_SOLUTIONDAY18_H
#define AOC2023_SOLUTIONDAY18_H

#include <fstream>

class SolutionDay18
{
public:
    explicit SolutionDay18(std::ifstream input);

    long solve1() const;

    long solve2() const;
private:
    long partOneSum = 0;
    long partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY18_H
