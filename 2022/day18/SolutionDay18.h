//
// Created by Augustin Grigorov on 18/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY18_H
#define AOC2022_SOLUTIONDAY18_H

#include <fstream>
#include <utility>

class SolutionDay18 {
public:
    explicit SolutionDay18(std::ifstream input);

    int solve1();

    int solve2();
private:
    int totalSurfaceArea = 0;
    int outerSurfaceArea = 0;
    std::pair<int, int> boundsX = std::make_pair(INT_MAX, INT_MIN);
    std::pair<int, int> boundsY = std::make_pair(INT_MAX, INT_MIN);
    std::pair<int, int> boundsZ = std::make_pair(INT_MAX, INT_MIN);
};


#endif //AOC2022_SOLUTIONDAY18_H
