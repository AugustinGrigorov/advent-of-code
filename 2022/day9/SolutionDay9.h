//
// Created by Augustin Grigorov on 09/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY9_H
#define AOC2022_SOLUTIONDAY9_H

#include <fstream>
#include <unordered_set>

class IntPairHash {
public:
    size_t operator()(std::pair<int, int> pair) const {
        std::hash<int> hash = {};
        auto hashProduct = hash(pair.first);
        hashProduct ^= hash(pair.second) + 0x517cc1b727220a95 + (hashProduct << 6) + (hashProduct >> 2);
        return hashProduct;
    }
};

class SolutionDay9 {
public:
    explicit SolutionDay9(std::ifstream input);

    size_t solve1();

    size_t solve2();
private:
    std::unordered_set<std::pair<int, int>, IntPairHash> partOneVisited = {};
    std::unordered_set<std::pair<int, int>, IntPairHash> partTwoVisited = {};
};


#endif //AOC2022_SOLUTIONDAY9_H
