#ifndef AOC2024_SolutionDay4_H
#define AOC2024_SolutionDay4_H

#include <fstream>

class SolutionDay4
{
public:
    explicit SolutionDay4(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSol = 0;
    int partTwoSol = 0;
};

#endif // AOC2024_SolutionDay4_H
