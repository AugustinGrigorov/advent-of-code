//
// Created by Augustin Grigorov on 11/12/2022.
//

#ifndef AOC2022_SOLUTIONDAY11_H
#define AOC2022_SOLUTIONDAY11_H

#include <fstream>
#include <utility>
#include <vector>
#include <deque>
#include <utility>

class Monkey {
public:
    std::vector<std::string> operation;
    int testDivisibleByValue = 0;
    int throwToIfTrue = 0;
    int throwToIfFalse = 0;
    long inspects = 0;
};

class UnoptimisedMonkey : public Monkey {
public:
    UnoptimisedMonkey(
            std::deque<int> items,
            std::vector<std::string> operation,
            int testDivisibleByValue,
            int throwToIfTrue,
            int throwToIfFalse
    ) {
        this->items = std::move(items);
        this->operation = std::move(operation);
        this->testDivisibleByValue = testDivisibleByValue;
        this->throwToIfTrue = throwToIfTrue;
        this->throwToIfFalse = throwToIfFalse;
    };
    std::deque<int> items;
};

class OptimisedMonkey : public Monkey {
public:
    OptimisedMonkey(
            std::deque<std::vector<std::pair<int, int>>> items,
            std::vector<std::string> operation,
            int testDivisibleByValue,
            int throwToIfTrue,
            int throwToIfFalse
    ) {
        this->items = std::move(items);
        this->operation = std::move(operation);
        this->testDivisibleByValue = testDivisibleByValue;
        this->throwToIfTrue = throwToIfTrue;
        this->throwToIfFalse = throwToIfFalse;
    };
    std::deque<std::vector<std::pair<int, int>>> items;
};

class SolutionDay11 {
public:
    explicit SolutionDay11(std::ifstream input);

    long solve1();

    long solve2();

private:
    std::vector<UnoptimisedMonkey> unoptimisedMonkeys = {};
    std::vector<OptimisedMonkey> optimisedMonkeys = {};
};


#endif //AOC2022_SOLUTIONDAY11_H
