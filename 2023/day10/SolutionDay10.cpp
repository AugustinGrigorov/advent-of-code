#include "SolutionDay10.h"
#include <iostream>
#include <limits>
#include <vector>
#include <regex>
#include <algorithm>

std::pair<int, int> getNextPos(
        std::pair<int, int> &prevPos,
        std::pair<int, int> &currentPos,
        std::vector<std::string> &terrainRepresentation
) {
    int x = currentPos.second;
    int y = currentPos.first;
    char validTopSymbols[3] = {'7', '|', 'F'};
    char validRightSymbols[3] = {'J', '-', '7'};
    char validBotSymbols[3] = {'J', '|', 'L'};
    char validLeftSymbols[3] = {'L', '-', 'F'};

    char currentSymbol = terrainRepresentation[y][x];
    switch (currentSymbol) {
        case 'S':
            if (y > 0 && std::ranges::contains(validTopSymbols, terrainRepresentation[y - 1][x])) {
                return std::make_pair(y - 1, x);
            }
            if (y < terrainRepresentation.size() &&
                std::ranges::contains(validBotSymbols, terrainRepresentation[y + 1][x])) {
                return std::make_pair(y + 1, x);
            }
            if (x > 0 && std::ranges::contains(validLeftSymbols, terrainRepresentation[y][x - 1])) {
                return std::make_pair(y, x - 1);
            }
            if (x < terrainRepresentation[y].size() &&
                std::ranges::contains(validRightSymbols, terrainRepresentation[y][x + 1])) {
                return std::make_pair(y, x + 1);
            }
        case '|':
            if (prevPos == std::make_pair(y - 1, x)) {
                return std::make_pair(y + 1, x);
            } else {
                return std::make_pair(y - 1, x);
            }
        case 'F':
            if (prevPos == std::make_pair(y + 1, x)) {
                return std::make_pair(y, x + 1);
            } else {
                return std::make_pair(y + 1, x);
            }
        case 'J':
            if (prevPos == std::make_pair(y - 1, x)) {
                return std::make_pair(y, x - 1);
            } else {
                return std::make_pair(y - 1, x);
            }
        case '-':
            if (prevPos == std::make_pair(y, x - 1)) {
                return std::make_pair(y, x + 1);
            } else {
                return std::make_pair(y, x - 1);
            }
        case '7':
            if (prevPos == std::make_pair(y + 1, x)) {
                return std::make_pair(y, x - 1);
            } else {
                return std::make_pair(y + 1, x);
            }
        case 'L':
            if (prevPos == std::make_pair(y - 1, x)) {
                return std::make_pair(y, x + 1);
            } else {
                return std::make_pair(y - 1, x);
            }
        default:
            throw std::runtime_error("Invalid state");
    }
}

SolutionDay10::SolutionDay10(std::ifstream input) {
    std::vector<std::string> terrainRepresentation = {};
    std::pair<int, int> beginningPos = {};
    std::vector<std::pair<int, int>> previouslyVisited = {};
    int lineNumber = 0;

    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            terrainRepresentation.push_back(line);
            size_t found = line.find('S');
            if (found != std::string::npos) {
                beginningPos = std::make_pair(found, lineNumber);
            }
            lineNumber++;
        }
    }

    int currentDepth = 1;
    auto prevPos = beginningPos;
    std::pair<int, int> currentPos = getNextPos(prevPos, beginningPos, terrainRepresentation);
    while (currentPos != beginningPos) {
        currentDepth++;
        auto nexPrevPos = currentPos;
        currentPos = getNextPos(prevPos, currentPos, terrainRepresentation);
        prevPos = nexPrevPos;
    }
    partOneSum = currentDepth / 2;
}

int SolutionDay10::solve1() const {
    return partOneSum;
}

int SolutionDay10::solve2() const {
    return partTwoSum;
}
