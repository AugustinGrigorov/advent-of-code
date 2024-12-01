#ifndef AOC2024_SOLUTIONDAY1_H
#define AOC2024_SOLUTIONDAY1_H

#include <fstream>

class SolutionDay1
{
public:
    explicit SolutionDay1(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSol = 0;
    int partTwoSol = 0;
};

#endif // AOC2024_SOLUTIONDAY1_H
