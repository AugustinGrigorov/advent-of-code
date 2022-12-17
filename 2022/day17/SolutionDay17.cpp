//
// Created by Augustin Grigorov on 17/12/2022.
//

#include "SolutionDay17.h"
#include <vector>
#include <iostream>

namespace {
    std::vector<std::pair<int, int>> getNextShape(uint64_t yOffset, uint64_t turn) {
        std::vector<std::pair<int, int>> shape = {};
        switch (turn % 5) {
            case 0:
                for (int x = 2; x < 6; ++x) {
                    shape.emplace_back(x, yOffset);
                }
                break;
            case 1:
                shape.emplace_back(3, yOffset + 2);
                shape.emplace_back(2, yOffset + 1);
                shape.emplace_back(3, yOffset + 1);
                shape.emplace_back(4, yOffset + 1);
                shape.emplace_back(3, yOffset);
                break;
            case 2:
                for (int y = 0; y < 3; ++y) {
                    shape.emplace_back(4, yOffset + y);
                }
                shape.emplace_back(2, yOffset);
                shape.emplace_back(3, yOffset);
                break;
            case 3:
                for (int y = 0; y < 4; ++y) {
                    shape.emplace_back(2, yOffset + y);
                }
                break;
            case 4:
                for (int x = 2; x < 4; ++x) {
                    for (int y = 0; y < 2; ++y) {
                        shape.emplace_back(x, yOffset + y);
                    }
                }
                break;
        }
        return shape;
    }

    bool moveShape(std::vector<std::pair<int, int>> &shape, char direction, std::vector<std::vector<bool>> &chamber) {
        switch (direction) {
            case '>':
                for (auto &point: shape) {
                    auto &[x, y] = point;
                    if (x == 6) {
                        return false;
                    }
                    if (chamber[y][x + 1]) {
                        return false;
                    }
                }
                for (auto &point: shape) {
                    auto &[x, _] = point;
                    x++;
                }
                return true;
            case '<':
                for (auto &point: shape) {
                    auto &[x, y] = point;
                    if (x == 0) {
                        return false;
                    }
                    if (chamber[y][x - 1]) {
                        return false;
                    }
                }
                for (auto &point: shape) {
                    auto &[x, _] = point;
                    x--;
                }
                return true;
            case 'v':
                for (auto &point: shape) {
                    auto &[x, y] = point;
                    if (y == 0) {
                        return false;
                    }
                    if (chamber[y - 1][x]) {
                        return false;
                    }
                }
                for (auto &point: shape) {
                    auto &[_, y] = point;
                    y--;
                }
                return true;
            default:
                throw std::runtime_error("Unexpected move direction");
        }
    }

    std::pair<uint64_t, uint64_t> findPattern (std::vector<std::vector<bool>> &chamber, int longestFall) {
        uint64_t start = chamber.size() - longestFall;
        uint64_t threshold = chamber.size() / 2;
        uint64_t patternLength = 0;
        assert(longestFall < threshold);
        uint64_t patternStartIndex = 0;
        for (uint64_t currentLineIndex = start; currentLineIndex > start - threshold; --currentLineIndex) {
            for (uint64_t evaluationLineIndex = currentLineIndex - 1; evaluationLineIndex > 0; --evaluationLineIndex) {
                auto &currentLine = chamber[currentLineIndex];
                auto &evaluationLine = chamber[evaluationLineIndex];
                if (currentLine == evaluationLine) {
                    bool allLinesMatch = true;
                    uint64_t potentialPatternLength = currentLineIndex - evaluationLineIndex;
                    for (int i = 0; i < potentialPatternLength; ++i) {
                        if (chamber[currentLineIndex - i] != chamber[evaluationLineIndex - i]) {
                            allLinesMatch = false;
                            break;
                        }
                    }
                    if (!allLinesMatch) continue;
                    auto patternCoversThreshold = true;
                    for (uint64_t i = evaluationLineIndex - potentialPatternLength; i > currentLineIndex - threshold && i > 0; --i) {
                        if (chamber[i] != chamber[i + potentialPatternLength]) {
                            patternCoversThreshold = false;
                            break;
                        }
                    }
                    if (patternCoversThreshold) {
                        patternLength = potentialPatternLength;
                        break;
                    }
                }
            }
            if (patternLength != 0) {
                patternStartIndex = currentLineIndex;
                break;
            }
        }
        return std::make_pair(patternStartIndex, patternLength);
    }
}


SolutionDay17::SolutionDay17(std::ifstream input) {
    std::vector<std::vector<bool>> chamber = {};
    int64_t currentHighest = 0L;
    int longestFall = 0;
    std::string line;
    getline(input, line);
    uint64_t minAmountOfEvaluationsNeeded = line.size() * 5;
    uint64_t directionIndex = 0;
    uint64_t linePatternStarted = 0;
    uint64_t pl = 0;
    uint64_t startCountingAtTurn = 0;
    uint64_t heightOffset = 0;
    uint64_t turnsNeededForPart2 = 1000000000000;
    for (uint64_t turn = 0; turn < turnsNeededForPart2; ++turn) {
        if (turn == 2022) {
            highestPointPart1 = currentHighest;
        }
        if (turn == minAmountOfEvaluationsNeeded) {
            auto [patternStartIndex, patternLength] = findPattern(chamber, longestFall);
            pl = patternLength;
            auto howManyLinesAgoCurrentPatternStart = (currentHighest - patternStartIndex) % patternLength;
            linePatternStarted = currentHighest - howManyLinesAgoCurrentPatternStart;
        }
        while (chamber.size() < currentHighest + 7) {
            std::vector<bool> row = {};
            for (int x = 0; x < 7; ++x) {
                row.push_back(false);
            }
            chamber.push_back(row);
        }
        auto currentShape = getNextShape(currentHighest + 3, turn);
        std::pair<int, int> *shapeHighestCoordinate = {};
        for (auto &point: currentShape) {
            if (shapeHighestCoordinate != nullptr) {
                int highestY = shapeHighestCoordinate->second;
                int y = point.second;
                if (y > highestY) {
                    shapeHighestCoordinate = &point;
                }
            } else {
                shapeHighestCoordinate = &point;
            }
        }
        bool canMoveDown = true;
        int currentFall = 0;
        while (canMoveDown) {
            currentFall++;
            if (directionIndex % line.size()) {}
            char direction = line[directionIndex % line.size()];
            directionIndex++;
            moveShape(currentShape, direction, chamber);
            canMoveDown = moveShape(currentShape, 'v', chamber);
        }
        if (currentFall > longestFall) {
            longestFall = currentFall;
        }
        for (auto &point: currentShape) {
            auto [x, y] = point;
            chamber[y][x] = true;
        }
        int potentialHighestPoint = shapeHighestCoordinate->second + 1;
        if (potentialHighestPoint > currentHighest) {
            currentHighest = potentialHighestPoint;
        }
        if (linePatternStarted != 0 && startCountingAtTurn == 0) {
            bool allTrue = true;
            for (int i = 0; i < pl; ++i) {
                if (linePatternStarted+i > chamber.size() -1) {
                    allTrue = false;
                    break;
                }
                if(chamber[linePatternStarted+i] != chamber[linePatternStarted+i - pl]) {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue) {
                startCountingAtTurn = turn;
            }
        }
        if (startCountingAtTurn != 0 && heightOffset == 0) {
            bool allTrue = true;
            for (int i = 0; i < pl; ++i) {
                if (linePatternStarted+i + pl > chamber.size() -1) {
                    allTrue = false;
                    break;
                }
                if(chamber[linePatternStarted+i] != chamber[linePatternStarted+i + pl]) {
                    allTrue = false;
                    break;
                }
            }
            if (allTrue) {
                auto turnsPerPattern = turn - startCountingAtTurn;
                auto skipAhead =(turnsNeededForPart2 - turn) / turnsPerPattern;
                heightOffset = skipAhead * pl;
                assert(heightOffset != 0);
                turn += skipAhead * turnsPerPattern;
                // calculate height offset
                // set the turn

            }
        }
    }
    highestPointPart2 = currentHighest + heightOffset;
}

int64_t SolutionDay17::solve1() {
    return highestPointPart1;
}

int64_t SolutionDay17::solve2() {
    return highestPointPart2;
}
