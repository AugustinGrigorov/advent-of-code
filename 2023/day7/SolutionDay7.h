#ifndef AOC2023_SOLUTIONDAY7_H
#define AOC2023_SOLUTIONDAY7_H

#include <fstream>
#include <map>
#include <utility>
#include <vector>

struct Hand {
public:
    Hand(std::string cards, int power1, int power2, int bet, std::vector<int> cardValues1, std::vector<int> cardValues2) : cards(std::move(cards)), power1(power1), power2(power2), bet(bet), cardValues1(std::move(cardValues1)), cardValues2(std::move(cardValues2)) {}

    std::string cards;
    int power1;
    int power2;
    int bet;
    std::vector<int> cardValues1;
    std::vector<int> cardValues2;
};

class SolutionDay7 {
public:
    explicit SolutionDay7(std::ifstream input);

    long solve1() const;

    int solve2() const;

private:
    long partOneSum = 0;
    int partTwoSum = 0;
};

#endif // AOC2023_SOLUTIONDAY7_H
