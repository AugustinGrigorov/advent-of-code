//
// Created by Augustin Grigorov on 06/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY6_H
#define AOC2022_SOLUTIONDAY6_H

#include <fstream>

class SolutionDay6 {
public:
    explicit SolutionDay6(std::ifstream input);

    int solve1();

    int solve2();
private:
    int positionOfStartOfPacketMarker;
    int positionOfStartOfMessageMarker;
};


#endif //AOC2022_SOLUTIONDAY6_H
