//
// Created by Augustin Grigorov on 02/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY2_H
#define AOC2022_SOLUTIONDAY2_H

#include <fstream>

class SolutionDay2 {
public:
    explicit SolutionDay2(std::ifstream input);

    int solve1();

    int solve2();

private:
    int score1 = 0;
    int score2 = 0;
};


#endif //AOC2022_SOLUTIONDAY2_H
