//
// Created by Augustin Grigorov on 09/12/2022.
//

#include "SolutionDay9.h"
#include <unordered_map>
#include <array>
#include <iostream>
#include <vector>

void follow(
        std::pair<int, int> &head,
        std::pair<int, int> &tail,
        std::unordered_set<std::pair<int, int>, IntPairHash> *visited
) {
    if (std::abs(head.first - tail.first) > 1 ||
        std::abs(head.second - tail.second) > 1) {
        int differenceX = head.first - tail.first;
        int differenceY = head.second - tail.second;
        int moveX = differenceX == 0 ? 0 : differenceX / std::abs(differenceX);
        int moveY = differenceY == 0 ? 0 : differenceY / std::abs(differenceY);

        tail.first += moveX;
        tail.second += moveY;

        if (visited != nullptr && !visited->contains(tail)) {
            visited->insert(tail);
        }
    }
}

void move(
        char direction,
        std::pair<int, int> &head
) {
    switch (direction) {
        case 'U':
            head.second += 1;
            break;
        case 'D':
            head.second -= 1;
            break;
        case 'R':
            head.first += 1;
            break;
        case 'L':
            head.first -= 1;
            break;
        default:
            break;
    }
}

SolutionDay9::SolutionDay9(std::ifstream input) {
    std::vector<std::pair<int, int>> longQueue = {};
    for (int i = 0; i < 10; ++i) {
        longQueue.emplace_back(0, 0);
    }

    partOneVisited.insert(std::make_pair(0, 0));
    partTwoVisited.insert(std::make_pair(0, 0));

    for (std::string line; getline(input, line);) {
        char direction = line[0];
        int amount = static_cast<int>(strtol(line.c_str() + 2, nullptr, 10));
        for (int i = 0; i < amount; ++i) {
            move(direction, longQueue[0]);
            for (size_t j = 1; j < longQueue.size(); ++j) {
                std::unordered_set<std::pair<int, int>, IntPairHash> *visited = {};
                if (j == 1) {
                    visited = &partOneVisited;
                }
                if (j == longQueue.size() - 1) {
                    visited = &partTwoVisited;
                }
                follow(longQueue[j - 1], longQueue[j], visited);
            }
        }
    }
}

size_t SolutionDay9::solve1() {
    return partOneVisited.size();
}

size_t SolutionDay9::solve2() {
    return partTwoVisited.size();
}