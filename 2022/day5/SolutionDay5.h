//
// Created by Augustin Grigorov on 05/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY5_H
#define AOC2022_SOLUTIONDAY5_H

#include <string>
#include <fstream>
#include <deque>
#include <vector>

class SolutionDay5 {
public:
    explicit SolutionDay5(std::ifstream input);

    std::string solve1();

    std::string solve2();

private:
    std::vector<std::deque<char>> stacksForPart1 = {};
    std::vector<std::deque<char>> stacksForPart2 = {};

    void simulateMovePart1(long amount, long from, long to);

    void simulateMovePart2(long amount, long from, long to);
};


#endif //AOC2022_SOLUTIONDAY5_H
