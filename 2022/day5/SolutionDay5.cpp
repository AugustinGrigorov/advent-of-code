//
// Created by Augustin Grigorov on 05/12/2022.
//

#include "SolutionDay5.h"

char *clearUntilNextInt(char *string) {
    while (!isdigit(string[0])) {
        string++;
    }
    return string;
}

SolutionDay5::SolutionDay5(std::ifstream input) {
    bool parsingCrates = true;
    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            if (parsingCrates) {
                for (int i = 0; i < line.size(); ++i) {
                    char c = line[i];
                    int stackNumber = i / 4;
                    if (c >= 'A' && c <= 'Z') {
                        while (stacksForPart1.size() < stackNumber + 1) {
                            stacksForPart1.emplace_back();
                        }
                        stacksForPart1[stackNumber].push_front(c);
                    }
                }
            } else {
                char *workingInput = line.data();
                workingInput = clearUntilNextInt(workingInput);
                long amount = strtol(workingInput, &workingInput, 10);
                workingInput = clearUntilNextInt(workingInput);
                long from = strtol(workingInput, &workingInput, 10);
                workingInput = clearUntilNextInt(workingInput);
                long to = strtol(workingInput, &workingInput, 10);
                simulateMovePart1(amount, from, to);
                simulateMovePart2(amount, from, to);
            }
        } else {
            parsingCrates = false;
            stacksForPart2 = stacksForPart1;
        }
    }
}

void SolutionDay5::simulateMovePart1(long amount, long from, long to) {
    for (int i = 0; i < amount; ++i) {
        char item = stacksForPart1[from - 1].back();
        stacksForPart1[from - 1].pop_back();
        stacksForPart1[to - 1].push_back(item);
    }
}

void SolutionDay5::simulateMovePart2(long amount, long from, long to) {
    std::deque<char> itemsToInsert = {};
    for (int i = 0; i < amount; ++i) {
        char item = stacksForPart2[from - 1].back();
        stacksForPart2[from - 1].pop_back();
        itemsToInsert.push_back(item);
    }
    while (!itemsToInsert.empty()) {
        stacksForPart2[to - 1].push_back(itemsToInsert.back());
        itemsToInsert.pop_back();
    }
}

std::string getTopOfEachStack(std::vector<std::deque<char>>& allStacks) {
    std::string topOfEachStack;
    for (auto &stack: allStacks) {
        topOfEachStack += stack.back();
    }
    return topOfEachStack;
}

std::string SolutionDay5::solve1() {
    return getTopOfEachStack(stacksForPart1);
}

std::string SolutionDay5::solve2() {
    return getTopOfEachStack(stacksForPart2);
}
