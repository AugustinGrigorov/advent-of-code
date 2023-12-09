#ifndef AOC2023_SOLUTIONDAY8_H
#define AOC2023_SOLUTIONDAY8_H

#include <fstream>

struct Node {
public:
    explicit Node () = default;
    std::string name;
    Node * left = nullptr;
    Node * right = nullptr;
};

class SolutionDay8
{
public:
    explicit SolutionDay8(std::ifstream input);

    int solve1() const;

    long solve2() const;
private:
    int partOneSum = 0;
    long partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY8_H
