#ifndef AOC2024_SOLUTIONDAY2_H
#define AOC2024_SOLUTIONDAY2_H

#include <fstream>

class SolutionDay2
{
public:
    explicit SolutionDay2(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int partOneSol = 0;
    int partTwoSol = 0;
};

#endif // AOC2024_SOLUTIONDAY2_H
