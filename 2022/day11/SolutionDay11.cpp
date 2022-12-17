//
// Created by Augustin Grigorov on 11/12/2022.
//

#include "SolutionDay11.h"
#include <sstream>
#include <iostream>
#include "../util/Util.h"

std::deque<int> parseItems(std::istringstream is) {
    std::deque<int> items = {};
    Util::discard(is, 2);
    std::string itemRaw;
    while (is && is >> itemRaw && !itemRaw.empty()) {
        int item = atoi(itemRaw.c_str());
        items.push_back(item);
    }
    return items;
}

std::vector<std::string> parseOperation(std::istringstream is) {
    std::vector<std::string> operation;
    std::string itemRaw;
    Util::discard(is, 3);
    while (is && is >> itemRaw && !itemRaw.empty()) {
        operation.push_back(itemRaw);
    }
    return operation;
}

int parseNumberAfter(std::istringstream is, int skips) {
    Util::discard(is, skips);
    std::string itemRaw;
    is >> itemRaw;
    int numericValue = atoi(itemRaw.c_str());
    return numericValue;
}

std::istringstream getNextLine(std::ifstream &input) {
    std::string line;
    getline(input, line);
    std::istringstream is{line};
    return is;
}

int performOperation(int item, std::vector<std::string> operation) {
    int operand1 = operation[0] == "old" ? item : atoi(operation[0].c_str());
    int operand2 = operation[2] == "old" ? item : atoi(operation[2].c_str());
    if (operation[1] == "+") {
        return operand1 + operand2;
    }
    if (operation[1] == "*") {
        return operand1 * operand2;
    }
    throw std::runtime_error("Unexpected operation");
}

template<typename ComparableMonkey>
bool compareMonkeys(ComparableMonkey m1, ComparableMonkey m2) {
    return m1.inspects > m2.inspects;
}

SolutionDay11::SolutionDay11(std::ifstream input) {
    while (input) {
        getNextLine(input);
        unoptimisedMonkeys.emplace_back(
                parseItems(getNextLine(input)),
                parseOperation(getNextLine(input)),
                parseNumberAfter(getNextLine(input), 3),
                parseNumberAfter(getNextLine(input), 5),
                parseNumberAfter(getNextLine(input), 5)

        );
        getNextLine(input);
    }
    std::vector<int> tests = {};
    for (const auto &monkey: unoptimisedMonkeys) {
        tests.emplace_back(monkey.testDivisibleByValue);
    }
    for (const auto &monkey: unoptimisedMonkeys) {
        std::deque<std::vector<std::pair<int, int>>> items = {};
        for (auto item: monkey.items) {
            std::vector<std::pair<int, int>> itemRepresentations = {};
            for (auto test: tests) {
                itemRepresentations.emplace_back(test, item % test);
            }
            items.push_back(itemRepresentations);
        }
        optimisedMonkeys.emplace_back(
                items,
                monkey.operation,
                monkey.testDivisibleByValue,
                monkey.throwToIfTrue,
                monkey.throwToIfFalse
        );
    }
    for (int i = 0; i < 20; ++i) {
        for (auto &monkey: unoptimisedMonkeys) {
            while (!monkey.items.empty()) {
                monkey.inspects++;
                auto elementPicked = monkey.items.front();
                monkey.items.pop_front();
                auto worryLevel = performOperation(elementPicked, monkey.operation) / 3;
                auto throwTo =
                        worryLevel % monkey.testDivisibleByValue == 0 ? monkey.throwToIfTrue : monkey.throwToIfFalse;
                unoptimisedMonkeys[throwTo].items.push_back(worryLevel);
            }
        }
    }
    for (int i = 0; i < 10000; ++i) {
        for (size_t j = 0; j < optimisedMonkeys.size(); ++j) {
            auto &optimisedMonkey = optimisedMonkeys[j];
            while (!optimisedMonkey.items.empty()) {
                optimisedMonkey.inspects++;
                auto elementPicked = optimisedMonkey.items.front();
                optimisedMonkey.items.pop_front();
                bool testIsTrue = false;
                for (auto &representation : elementPicked) {
                    auto [test, value] = representation;
                    representation.second = performOperation(value, optimisedMonkey.operation) % test;
                    if (optimisedMonkey.testDivisibleByValue == test && representation.second == 0) {
                        testIsTrue = true;
                    }
                }
                auto throwTo = testIsTrue ? optimisedMonkey.throwToIfTrue : optimisedMonkey.throwToIfFalse;
                optimisedMonkeys[throwTo].items.push_back(elementPicked);
            }
        }
    }
}

long SolutionDay11::solve1() {
    auto monkeyRanking = unoptimisedMonkeys;
    std::sort(monkeyRanking.begin(), monkeyRanking.end(), compareMonkeys<UnoptimisedMonkey>);
    return monkeyRanking[0].inspects * monkeyRanking[1].inspects;
}

long SolutionDay11::solve2() {
    auto monkeyRanking = optimisedMonkeys;
    std::sort(monkeyRanking.begin(), monkeyRanking.end(), compareMonkeys<OptimisedMonkey>);
    return monkeyRanking[0].inspects * monkeyRanking[1].inspects;
}
