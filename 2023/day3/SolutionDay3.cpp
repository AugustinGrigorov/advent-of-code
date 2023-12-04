#include "SolutionDay3.h"
#include <iostream>
#include <limits>
#include <map>
#include <set>

bool isSpecialSymbol(char c) {
    return !isdigit(c) && c != '.';
}

SolutionDay3::SolutionDay3(std::ifstream input) {
    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            std::vector<char> row = {};
            for (char c: line) {
                row.push_back(c);
            }
            engineSchematic.push_back(row);
        }
    }
    std::map<std::pair<int, int>, std::vector<int>> starAdjacentNumbers = {};
    std::string currentNumber = {};
    bool isAdjacentToSymbol = false;
    std::set<std::pair<int, int>> adjacentStars = {};
    for (int y = 0; y < engineSchematic.size(); ++y) {
        for (int x = 0; x < engineSchematic[y].size(); ++x) {
            if (isdigit(engineSchematic[y][x])) {
                currentNumber += engineSchematic[y][x];
                std::vector<std::pair<std::pair<int, int>, char>> neighbours = getNeighbouringSymbols(x, y);
                for (std::pair<std::pair<int, int>, char> neighbour: neighbours) {
                    if (isSpecialSymbol(neighbour.second)) {
                        isAdjacentToSymbol = true;
                    }
                    if (neighbour.second == '*') {
                        adjacentStars.insert(neighbour.first);
                    }
                }
            } else {
                processNumber(currentNumber, isAdjacentToSymbol, adjacentStars, starAdjacentNumbers);
            }
        }
        processNumber(currentNumber, isAdjacentToSymbol, adjacentStars, starAdjacentNumbers);
    }
    for (const auto& kv: starAdjacentNumbers) {
        std::vector<int> numbers = kv.second;
        if (numbers.size() == 2) {
            partTwoSum += numbers[0] * numbers[1];
        }
    }
}

void SolutionDay3::processNumber(
        std::string &currentNumber, bool &isAdjacentToSymbol,
        std::set<std::pair<int, int>> &adjacentStars,
        std::map<std::pair<int, int>, std::vector<int>> &starAdjacentNumbers
        ) {
    if (currentNumber.length() > 0 && isAdjacentToSymbol) {
        partOneSum += static_cast<int>(strtol(currentNumber.c_str(), nullptr, 10));
    }
    if (currentNumber.length() > 0 && !adjacentStars.empty()){
        for (std::pair<int, int> star: adjacentStars) {
            starAdjacentNumbers[star].push_back(static_cast<int>(strtol(currentNumber.c_str(), nullptr, 10)));
        }
    }
    adjacentStars = {};
    isAdjacentToSymbol = false;
    currentNumber = "";
}

std::vector<std::pair<std::pair<int, int>, char>> SolutionDay3::getNeighbouringSymbols(int x, int y) const {
    std::vector<std::pair<std::pair<int, int>, char>> neighbours = std::vector<std::pair<std::pair<int, int>, char>>{};
    for (int j = y - 1; j <= y + 1; ++j) {
        for (int i = x - 1; i <= x + 1; ++i) {
            if (j == y && i == x) continue;
            if (j > 0 && i > 0 && j < engineSchematic.size() && i < engineSchematic[j].size()) {
                std::pair<int, char> {1, 'c'};
                std::pair<std::pair<int, int>, char> entry = std::make_pair(std::make_pair(j,i), engineSchematic[j][i]);
                neighbours.push_back(entry);
            }
        }
    }
    return neighbours;
}

int SolutionDay3::solve1() const {
    return partOneSum;
}

long SolutionDay3::solve2() const {
    return partTwoSum;
}
