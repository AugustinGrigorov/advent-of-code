#ifndef AOC2023_SOLUTIONDAY4_H
#define AOC2023_SOLUTIONDAY4_H

#include <fstream>
#include <sstream>

class SolutionDay4
{
public:
    explicit SolutionDay4(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY4_H
