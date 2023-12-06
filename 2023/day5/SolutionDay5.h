#ifndef AOC2023_SOLUTIONDAY5_H
#define AOC2023_SOLUTIONDAY5_H

#include <fstream>
#include <limits>

class SolutionDay5
{
public:
    explicit SolutionDay5(std::ifstream input);

    long solve1() const;

    long solve2() const;
private:
    long minDistance = std::numeric_limits<long>::max();
    long partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY5_H
