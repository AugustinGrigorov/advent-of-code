#ifndef AOC2023_SOLUTIONDAY6_H
#define AOC2023_SOLUTIONDAY6_H

#include <fstream>

class SolutionDay6
{
public:
    explicit SolutionDay6(std::ifstream input);

    long solve1() const;

    long solve2() const;
private:
    long waysOfWinningPerRaceProduct = 1;
    long waysOfWinningBigRace = 0;
};

#endif // AOC2023_SOLUTIONDAY6_H
