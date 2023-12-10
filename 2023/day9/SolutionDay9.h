#ifndef AOC2023_SOLUTIONDAY9_H
#define AOC2023_SOLUTIONDAY9_H

#include <fstream>
#include <sstream>

class SolutionDay9
{
public:
    explicit SolutionDay9(std::ifstream input);

    long solve1() const;

    long solve2() const;
private:
    long partOneSum = 0;
    long partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY9_H
