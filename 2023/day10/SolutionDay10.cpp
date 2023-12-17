#include "SolutionDay10.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <set>
#include <cassert>

int findSizeOfAreaBetweenWalls(std::pair<int, int> rootPos, int width, int height,
                               std::set<std::pair<int, int>> &visitedSoFar) {
    if (visitedSoFar.contains(rootPos)) return 0;
    if (rootPos.first < 0 || rootPos.second < 0 || rootPos.first >= height || rootPos.second >= width) return 0;
    visitedSoFar.insert(rootPos);
    return 1 +
           findSizeOfAreaBetweenWalls(std::make_pair(rootPos.first - 1, rootPos.second), width, height, visitedSoFar) +
           findSizeOfAreaBetweenWalls(std::make_pair(rootPos.first + 1, rootPos.second), width, height, visitedSoFar) +
           findSizeOfAreaBetweenWalls(std::make_pair(rootPos.first, rootPos.second + 1), width, height, visitedSoFar) +
           findSizeOfAreaBetweenWalls(std::make_pair(rootPos.first, rootPos.second - 1), width, height, visitedSoFar);
}

std::pair<int, int> getNextPos(
        std::pair<int, int> &prevPos,
        std::pair<int, int> &currentPos,
        std::vector<std::string> &terrainRepresentation,
        std::pair<int, int> &leftRightTurns,
        bool part1,
        int &areaSoFar,
        std::set<std::pair<int, int>> &visitedSoFar
) {
    visitedSoFar.insert(currentPos);
    int x = currentPos.second;
    int y = currentPos.first;
    char validTopSymbols[3] = {'7', '|', 'F'};
    char validRightSymbols[3] = {'J', '-', '7'};
    char validBotSymbols[3] = {'J', '|', 'L'};
    char validLeftSymbols[3] = {'L', '-', 'F'};
    int height = terrainRepresentation.size();
    int width = terrainRepresentation[0].size();

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
                // going down v
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // check left
                        auto posToStartChecking = std::make_pair(currentPos.first, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    } else {
                        // check right
                        auto posToStartChecking = std::make_pair(currentPos.first, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    }
                }
                return std::make_pair(y + 1, x);
            } else {
                // going up ^
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        auto posToStartChecking = std::make_pair(currentPos.first, currentPos.second - 1);

                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    } else {
                        auto posToStartChecking = std::make_pair(currentPos.first, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    }
                }
                return std::make_pair(y - 1, x);
            }
        case 'F':
            if (prevPos == std::make_pair(y + 1, x)) {
                // turn right
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x-1 y
                        auto posToStartChecking = std::make_pair(currentPos.first, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x y-1
                        posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x+1 y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.second++;
                return std::make_pair(y, x + 1);
            } else {
                // turn left
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x+1 y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x-1 y
                        auto posToStartChecking = std::make_pair(currentPos.first, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x y-1
                        posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.first++;
                return std::make_pair(y + 1, x);
            }
        case 'J':
            if (prevPos == std::make_pair(y - 1, x)) {
                // turn right
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x+1 y
                        posToStartChecking = std::make_pair(currentPos.first, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x-1 y-1
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.second++;
                return std::make_pair(y, x - 1);
            } else {
                // turn left
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x-1 y-1
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x+1 y
                        posToStartChecking = std::make_pair(currentPos.first, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.first++;
                return std::make_pair(y - 1, x);
            }
        case '-':
            if (prevPos == std::make_pair(y, x - 1)) {
                // going right ->
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    } else {
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    }
                }
                return std::make_pair(y, x + 1);
            } else {
                // going left <-
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    } else {
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    }
                }
                return std::make_pair(y, x - 1);
            }
        case '7':
            if (prevPos == std::make_pair(y + 1, x)) {
                // turn left
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x-1 y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x y-1
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x+1 y
                        posToStartChecking = std::make_pair(currentPos.first, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.first++;
                return std::make_pair(y, x - 1);
            } else {
                // turn right
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x y-1
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x+1 y
                        posToStartChecking = std::make_pair(currentPos.first, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x-1 y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.second++;
                return std::make_pair(y + 1, x);
            }
        case 'L':
            if (prevPos == std::make_pair(y - 1, x)) {
                // turn left
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x+1 y-1
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x-1 y
                        posToStartChecking = std::make_pair(currentPos.first, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);
                    }
                }
                if (part1) leftRightTurns.first++;
                return std::make_pair(y, x + 1);
            } else {
                // turn right
                if (!part1) {
                    if (leftRightTurns.first > leftRightTurns.second) {
                        // x y+1
                        auto posToStartChecking = std::make_pair(currentPos.first + 1, currentPos.second);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                        // x-1 y
                        posToStartChecking = std::make_pair(currentPos.first, currentPos.second - 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    } else {
                        // x+1 y-1
                        auto posToStartChecking = std::make_pair(currentPos.first - 1, currentPos.second + 1);
                        areaSoFar += findSizeOfAreaBetweenWalls(posToStartChecking, width, height, visitedSoFar);

                    }
                }
                if (part1) leftRightTurns.second++;
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
                beginningPos = std::make_pair(lineNumber, found);
            }
            lineNumber++;
        }
    }

    int currentDepth = 1;
    int areaSoFar = 0;
    std::set<std::pair<int, int>> visitedSoFar = {};
    std::pair<int, int> leftRightPairs = {};

    auto prevPos = beginningPos;
    std::pair<int, int> currentPos = getNextPos(prevPos, beginningPos, terrainRepresentation, leftRightPairs, true,
                                                areaSoFar, visitedSoFar);
    while (currentPos != beginningPos) {
        currentDepth++;
        auto nexPrevPos = currentPos;
        currentPos = getNextPos(prevPos, currentPos, terrainRepresentation, leftRightPairs, true, areaSoFar,
                                visitedSoFar);
        prevPos = nexPrevPos;
    }

    partOneSum = currentDepth / 2;
    assert(areaSoFar == 0);



    prevPos = beginningPos;
    currentPos = getNextPos(prevPos, beginningPos, terrainRepresentation, leftRightPairs, false,
                            areaSoFar, visitedSoFar);
    while (currentPos != beginningPos) {
        auto nexPrevPos = currentPos;
        currentPos = getNextPos(prevPos, currentPos, terrainRepresentation, leftRightPairs, false, areaSoFar,
                                visitedSoFar);
        prevPos = nexPrevPos;
    }
    partTwoSum = areaSoFar;

    std::string result = "";
    for (int y = 0; y < 10; ++y) {
        for (int x = 0; x < 20; ++x) {
            if (visitedSoFar.contains(std::make_pair(y, x))) {
                result += "#";
            } else {
                result += ".";
            }
        }
        result += "\n";
    }
    std::cout << result;
}

int SolutionDay10::solve1() const {
    return partOneSum;
}

int SolutionDay10::solve2() const {
    return partTwoSum;
}
