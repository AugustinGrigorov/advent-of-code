#ifndef AOC2023_SOLUTIONDAY3_H
#define AOC2023_SOLUTIONDAY3_H

#include <fstream>
#include <vector>
#include <set>
#include <map>

class SolutionDay3
{
public:
    explicit SolutionDay3(std::ifstream input);

    int solve1() const;

    long solve2() const;
private:
    std::vector<std::vector<char>> engineSchematic = {};
    int partOneSum = 0;
    long partTwoSum = 0;

    std::vector<std::pair<std::pair<int, int>, char>> getNeighbouringSymbols(int x, int y) const;

    void
    processNumber(std::string &currentNumber, bool &isAdjacentToSymbol, std::set<std::pair<int, int>> &adjacentStars,
                  std::map<std::pair<int, int>, std::vector<int>> &starAdjacentNumbers);
};

#endif // AOC2023_SOLUTIONDAY1_H
