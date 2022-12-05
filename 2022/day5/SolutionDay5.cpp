//
// Created by Augustin Grigorov on 05/12/2022.
//

#include "SolutionDay5.h"
#include <fstream>
#include <vector>
#include <deque>

char * clearUntilNextInt(char * string) {
    while (!isdigit(string[0])) {
        string++;
    }
    return string;
}

SolutionDay5::SolutionDay5() {
    std::string line;
    std::ifstream input;
    input.open("day5/input");
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    std::vector<std::deque<char>> stacksForPart1 = {};
    std::vector<std::deque<char>> stacksForPart2 = {};
    bool parsingCrates = true;
    while (getline(input, line)) {
        if (!line.empty()) {
            if (parsingCrates) {
                for (int i = 0; i < line.size(); ++i) {
                    char c = line[i];
                    int stackNumber = i / 4;
                    if (c>='A' && c<='Z') {
                        while (stacksForPart1.size() < stackNumber + 1) {
                            stacksForPart1.emplace_back();
                        }
                        stacksForPart1[stackNumber].push_front(c);
                    }
                }
            } else {
                char * workingInput = line.data();
                workingInput = clearUntilNextInt(workingInput);
                long amount = strtol(workingInput, &workingInput, 10);
                workingInput = clearUntilNextInt(workingInput);
                long from = strtol(workingInput, &workingInput, 10);
                workingInput = clearUntilNextInt(workingInput);
                long to = strtol(workingInput, &workingInput, 10);
                for (int i = 0; i < amount; ++i) {
                    char item = stacksForPart1[from - 1].back();
                    stacksForPart1[from - 1].pop_back();
                    stacksForPart1[to - 1].push_back(item);
                }
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
        }
        else {
            parsingCrates = false;
            stacksForPart2 = stacksForPart1;
        }
    }
    for (auto & stack: stacksForPart1) {
        topOfEachStack1 += stack.back();
    }
    for (auto & stack: stacksForPart2) {
        topOfEachStack2 += stack.back();
    }
}

std::string SolutionDay5::solve1() {
    return topOfEachStack1;
}

std::string SolutionDay5::solve2() {
    return topOfEachStack2;
}
