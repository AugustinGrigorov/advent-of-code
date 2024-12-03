#ifndef AOC2024_SOLUTIONDAY3_H
#define AOC2024_SOLUTIONDAY3_H

#include <fstream>

class SolutionDay3
{
public:
    explicit SolutionDay3(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSol = 0;
    int partTwoSol = 0;
};

#endif // AOC2024_SOLUTIONDAY3_H
