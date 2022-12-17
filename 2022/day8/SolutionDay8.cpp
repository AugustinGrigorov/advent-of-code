//
// Created by Augustin Grigorov on 08/12/2022.
//

#include "SolutionDay8.h"
#include <map>
#include <iostream>

void evaluateTree(std::vector<std::vector<int>> &treeHeightMap, std::vector<std::vector<bool>> &visibleFromDirection,
                  size_t x, size_t y, int &tallestTreeSoFar, int &numberOfVisibleTrees) {
    if (treeHeightMap[y][x] > tallestTreeSoFar) {
        if (!visibleFromDirection[y][x]) {
            numberOfVisibleTrees++;
            visibleFromDirection[y][x] = true;
        }
        tallestTreeSoFar = treeHeightMap[y][x];
    }
}

SolutionDay8::SolutionDay8(std::ifstream input) {
    std::vector<std::vector<int>> treeHeightMap = {};
    for (std::string line; getline(input, line);) {
        std::vector<int> row = {};
        for (char c: line) {
            row.push_back(c - '0');
        }
        treeHeightMap.push_back(row);
    }

    // Part 1
    std::vector<std::vector<bool>> visible = {};
    for (size_t y = 0; y < treeHeightMap.size(); ++y) {
        std::vector<bool> row = {};
        for (size_t x = 0; x < treeHeightMap[0].size(); ++x) {
            row.push_back(false);
        }
        visible.push_back(row);
    }
    for (size_t x = 0; x < treeHeightMap[0].size(); ++x) {
        int tallestTreeSoFar = -1;
        for (size_t y = treeHeightMap.size(); y-- > 0;) {
            evaluateTree(treeHeightMap, visible, x, y, tallestTreeSoFar, numberOfVisibleTrees);
        }
    }
    for (size_t x = 0; x < treeHeightMap[0].size(); ++x) {
        int tallestTreeSoFar = -1;
        for (size_t y = 0; y < treeHeightMap.size(); ++y) {
            evaluateTree(treeHeightMap, visible, x, y, tallestTreeSoFar, numberOfVisibleTrees);
        }
    }
    for (size_t y = 0; y < treeHeightMap.size(); ++y) {
        int tallestTreeSoFar = -1;
        for (size_t x = treeHeightMap.size(); x-- > 0;) {
            evaluateTree(treeHeightMap, visible, x, y, tallestTreeSoFar, numberOfVisibleTrees);
        }
    }
    for (size_t y = 0; y < treeHeightMap.size(); ++y) {
        int tallestTreeSoFar = -1;
        for (size_t x = 0; x < treeHeightMap[0].size(); ++x) {
            evaluateTree(treeHeightMap, visible, x, y, tallestTreeSoFar, numberOfVisibleTrees);
        }
    }

    // Part 2
    for (size_t y = 0; y < treeHeightMap.size(); ++y) {
        for (size_t x = 0; x < treeHeightMap[y].size(); ++x) {
            int roomRight = 0;
            for (size_t xr = x + 1; xr < treeHeightMap.size(); ++xr) {
                roomRight++;
                if (treeHeightMap[y][xr] >= treeHeightMap[y][x]) {
                    break;
                }
            }
            int roomLeft = 0;
            for (auto xl = x; xl-- > 0;) {
                roomLeft++;
                if (treeHeightMap[y][xl] >= treeHeightMap[y][x]) {
                    break;
                }
            }
            int roomDown = 0;
            for (size_t yd = y + 1; yd < treeHeightMap.size(); ++yd) {
                roomDown++;
                if (treeHeightMap[yd][x] >= treeHeightMap[y][x]) {
                    break;
                }
            }
            int roomUp = 0;
            for (auto yu = y; yu-- > 0;) {
                roomUp++;
                if (treeHeightMap[yu][x] >= treeHeightMap[y][x]) {
                    break;
                }
            }
            int currentScenicScore = roomLeft * roomRight * roomUp * roomDown;
            if (currentScenicScore > biggestScenicScore) {
                biggestScenicScore = currentScenicScore;
            }
        }
    }
}

int SolutionDay8::solve1() {
    return numberOfVisibleTrees;
}

int SolutionDay8::solve2() {
    return biggestScenicScore;
}

