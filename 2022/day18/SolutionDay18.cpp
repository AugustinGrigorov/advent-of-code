//
// Created by Augustin Grigorov on 18/12/2022.
//

#include "SolutionDay18.h"
#include <array>
#include <unordered_set>
#include <functional>
#include <iostream>
#include <vector>

class ThreeIntArrayHash {
public:
    size_t operator()(std::array<int, 3> array) const {
        auto key = std::to_string(array[0]) + "," + std::to_string(array[1]) + "," + std::to_string(array[2]);
        return std::hash<std::string>()(key);
    }
};

std::array<int, 3> parseLine(std::string &line) {
    std::array<int, 3> coordinates = {};
    std::string currentCoordinate;
    int coordinateIndex = 0;
    for (char c: line) {
        if (c == ',') {
            coordinates[coordinateIndex] = atoi(currentCoordinate.c_str());
            coordinateIndex++;
            currentCoordinate = "";
        } else {
            currentCoordinate += c;
        }
    }
    coordinates[coordinateIndex] = atoi(currentCoordinate.c_str());
    assert(coordinateIndex == 2);
    return coordinates;
}

std::vector<std::array<int, 3>> getSurroundingNodes(std::array<int, 3> elementCoordinates,
                                                    std::unordered_set<std::array<int, 3>, ThreeIntArrayHash> &problemSpace) {
    std::vector<std::array<int, 3>> neighbours = {};
    for (int i = 0; i < 3; ++i) {
        std::array<int, 3> neighbourLocation1 = elementCoordinates;
        std::array<int, 3> neighbourLocation2 = elementCoordinates;
        neighbourLocation1[i] += 1;
        if (problemSpace.contains(neighbourLocation1)) {
            neighbours.push_back(neighbourLocation1);
        }
        neighbourLocation2[i] -= 1;
        if (problemSpace.contains(neighbourLocation2)) {
            neighbours.push_back(neighbourLocation2);
        }
    }
    assert(neighbours.size() <= 6);
    return neighbours;
}

std::array<int, 3> findOneOuterEdgeSquare(
        std::pair<int, int> boundsX,
        std::pair<int, int> boundsY,
        std::pair<int, int> boundsZ,
        std::unordered_set<std::array<int, 3>, ThreeIntArrayHash> &problemSpace
) {
    auto &[lowerX, upperX] = boundsX;
    auto &[lowerY, upperY] = boundsY;
    auto &[lowerZ, upperZ] = boundsZ;
    for (int x = lowerX; x <= upperX; ++x) {
        for (int y = lowerY; y <= upperY; ++y) {
            for (int z = lowerZ; z <= upperZ; ++z) {
                auto candidate = std::array{x,y,z};
                if (problemSpace.contains(candidate)) {
                    return candidate;
                }
            }
        }
    }
    throw std::runtime_error("Expected to find at least one item");
}

int findSurfaceAreaAround(std::array<int, 3> start, std::unordered_set<std::array<int, 3>, ThreeIntArrayHash> &problemSpace){
    std::unordered_set<std::array<int, 3>, ThreeIntArrayHash> visited = {};
    std::vector<std::array<int, 3>> toVisit = {};
    toVisit.push_back(start);
    int totalArea = 0;
    while (!toVisit.empty()) {
        auto nextElement = toVisit.back();
        visited.insert(nextElement);
        auto surroundingNodes = getSurroundingNodes(nextElement, problemSpace);
        totalArea += 6 - static_cast<int>(surroundingNodes.size());
        toVisit.pop_back();
        for (auto neighbour : surroundingNodes) {
            if (!visited.contains(neighbour) && std::find(toVisit.begin(), toVisit.end(), neighbour) == toVisit.end()) {
                toVisit.push_back(neighbour);
            }
        }
    }
    return totalArea;
}

SolutionDay18::SolutionDay18(std::ifstream input) {
    std::unordered_set<std::array<int, 3>, ThreeIntArrayHash> problemSpace = {};
    for (std::string line; getline(input, line);) {
        auto elementCoordinates = parseLine(line);
        problemSpace.insert(elementCoordinates);
        auto [elX, elY, elZ] = elementCoordinates;
        auto &[lowerX, upperX] = boundsX;
        auto &[lowerY, upperY] = boundsY;
        auto &[lowerZ, upperZ] = boundsZ;
        if (elX < lowerX) {
            lowerX = elX;
        }
        if (elX > upperX) {
            upperX = elX;
        }
        if (elY < lowerY) {
            lowerY = elY;
        }
        if (elY > upperY) {
            upperY = elY;
        }
        if (elZ < lowerZ) {
            lowerZ = elZ;
        }
        if (elZ > upperZ) {
            upperZ = elZ;
        }
    }
    for (auto &element: problemSpace) {
        int neighboursCount = static_cast<int>(getSurroundingNodes(element, problemSpace).size());
        totalSurfaceArea += (6 - neighboursCount);
    }

    auto start = findOneOuterEdgeSquare(boundsX, boundsY, boundsZ, problemSpace);
    outerSurfaceArea = findSurfaceAreaAround(start, problemSpace);
}

int SolutionDay18::solve1() {
    return totalSurfaceArea;
}

int SolutionDay18::solve2() {
    return outerSurfaceArea;
}
