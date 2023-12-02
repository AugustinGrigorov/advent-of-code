#ifndef AOC2023_SOLUTIONDAY2_H
#define AOC2023_SOLUTIONDAY2_H

#include <fstream>

class SolutionDay2
{
public:
    explicit SolutionDay2(std::ifstream input);

    int solve1() const;

    int solve2() const;
private:
    int validGames = 0;
    long cubePowers = 0;
};

#endif // AOC2023_SOLUTIONDAY2_H
