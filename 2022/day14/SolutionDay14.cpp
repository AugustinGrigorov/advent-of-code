//
// Created by Augustin Grigorov on 14/12/2022.
//

#include "SolutionDay14.h"
#include <sstream>
#include <utility>
#include <vector>
#include <iostream>
#include <unordered_map>

class IntPairHash {
public:
    size_t operator()(std::pair<int, int> pair) const {
        std::hash<int> hash = {};
        auto hashProduct = hash(pair.first);
        hashProduct ^= hash(pair.second) + 0x517cc1b727220a95 + (hashProduct << 6) + (hashProduct >> 2);
        return hashProduct;
    }
};

void drawRock(std::vector<std::pair<int, int>> &rockRepresentation,
              std::unordered_map<std::pair<int, int>, char, IntPairHash> &map) {
    auto currentPoint = rockRepresentation[0];
    for (size_t i = 1; i < rockRepresentation.size(); ++i) {
        auto diffX = currentPoint.first - rockRepresentation[i].first;
        auto diffY = currentPoint.second - rockRepresentation[i].second;
        assert(diffX == 0 || diffY == 0);
        if (diffX != 0) {
            int smaller, bigger;
            if (diffX > 0) {
                smaller = rockRepresentation[i].first;
                bigger = currentPoint.first;
            } else {
                smaller = currentPoint.first;
                bigger = rockRepresentation[i].first;
            }
            for (; smaller < bigger + 1; ++smaller) {
                map[std::make_pair(smaller, currentPoint.second)] = '#';
            }
        }
        if (diffY != 0) {
            int smaller, bigger;
            if (diffY > 0) {
                smaller = rockRepresentation[i].second;
                bigger = currentPoint.second;
            } else {
                smaller = currentPoint.second;
                bigger = rockRepresentation[i].second;
            }
            for (; smaller < bigger + 1; ++smaller) {
                map[std::make_pair(currentPoint.first, smaller)] = '#';
            }
        }
        currentPoint = rockRepresentation[i];
    }
}

void printMap(std::unordered_map<std::pair<int, int>, char, IntPairHash> &caveMap) {
    for (int y = 0; y < 14; ++y) {
        for (int x = 484; x < 510; ++x) {
            auto val = caveMap[std::make_pair(x,y)];
            auto print =  (val == 0) ? '.' : val;
            std::cout << print;
        }
        std::cout << std::endl;
    }
}

SolutionDay14::SolutionDay14(std::ifstream input) {
    std::vector<std::vector<std::pair<int, int>>> allRockStructures = {};
    for (std::string line; getline(input, line);) {
        std::istringstream is{line};
        std::string discard;
        std::vector<std::pair<int, int>> points = {};
        while (is) {
            std::string nextPointRaw;
            is >> nextPointRaw;
            is >> discard;
            auto commaIndex = nextPointRaw.find(',');
            auto firstNum = atoi(nextPointRaw.substr(0, commaIndex).c_str());
            auto secondNum = atoi(nextPointRaw.substr(commaIndex + 1).c_str());
            if (secondNum > lowestPoint) {
                lowestPoint = secondNum;
            }
            points.emplace_back(firstNum, secondNum);
        }
        allRockStructures.push_back(std::move(points));
    }
    std::unordered_map<std::pair<int, int>, char, IntPairHash> caveMap = {};
    for (auto &rockRepresentation: allRockStructures) {
        drawRock(rockRepresentation, caveMap);
    }
    auto unitOfSandCoordinates = std::make_pair(500,0);
    while (unitOfSandCoordinates.second < lowestPoint) {
        if(caveMap[std::make_pair(unitOfSandCoordinates.first, unitOfSandCoordinates.second+1)] == 0) {
            unitOfSandCoordinates = std::make_pair(unitOfSandCoordinates.first, unitOfSandCoordinates.second+1);
            continue;
        }
        if(caveMap[std::make_pair(unitOfSandCoordinates.first - 1, unitOfSandCoordinates.second + 1)] == 0) {
            unitOfSandCoordinates = std::make_pair(unitOfSandCoordinates.first - 1, unitOfSandCoordinates.second + 1);
            continue;
        }
        if(caveMap[std::make_pair(unitOfSandCoordinates.first + 1, unitOfSandCoordinates.second + 1)] == 0) {
            unitOfSandCoordinates = std::make_pair(unitOfSandCoordinates.first + 1, unitOfSandCoordinates.second + 1);
            continue;
        }
        caveMap[unitOfSandCoordinates] = 'o';
        unitsOfSandInCavePart1++;
        unitOfSandCoordinates = std::make_pair(500,0);
    }
    unitOfSandCoordinates = std::make_pair(500,0);
    unitsOfSandInCavePart2 = unitsOfSandInCavePart1;
    while (caveMap[unitOfSandCoordinates] != 'o') {
        if(unitOfSandCoordinates.second == lowestPoint + 1) {
            caveMap[unitOfSandCoordinates] = 'o';
            unitsOfSandInCavePart2++;
            unitOfSandCoordinates = std::make_pair(500,0);
            continue;
        }
        if(caveMap[std::make_pair(unitOfSandCoordinates.first, unitOfSandCoordinates.second+1)] == 0) {
            unitOfSandCoordinates = std::make_pair(unitOfSandCoordinates.first, unitOfSandCoordinates.second+1);
            continue;
        }
        if(caveMap[std::make_pair(unitOfSandCoordinates.first - 1, unitOfSandCoordinates.second + 1)] == 0) {
            unitOfSandCoordinates = std::make_pair(unitOfSandCoordinates.first - 1, unitOfSandCoordinates.second + 1);
            continue;
        }
        if(caveMap[std::make_pair(unitOfSandCoordinates.first + 1, unitOfSandCoordinates.second + 1)] == 0) {
            unitOfSandCoordinates = std::make_pair(unitOfSandCoordinates.first + 1, unitOfSandCoordinates.second + 1);
            continue;
        }
        caveMap[unitOfSandCoordinates] = 'o';
        unitsOfSandInCavePart2++;
        unitOfSandCoordinates = std::make_pair(500,0);
    }
}

int SolutionDay14::solve1() {
    return unitsOfSandInCavePart1;
}

int SolutionDay14::solve2() {
    return unitsOfSandInCavePart2;
}
