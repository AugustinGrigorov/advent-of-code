//
// Created by Augustin Grigorov on 12/12/2022.
//

#include "SolutionDay12.h"
#include <utility>
#include <vector>
#include <iostream>
#include <queue>

class Node {
public:
    Node(int height, std::pair<int, int> coordinates)
            : height(height), coordinates(std::move(coordinates)) {}

    const int height;
    bool visited = false;
    int shortestPath = INT_MAX;
    std::pair<int, int> coordinates;
};

bool compareNodes(Node *n1, Node *n2) {
    int v1 = n1->visited ? INT_MAX : n1->height;
    int v2 = n2->visited ? INT_MAX : n2->height;
    return v1 < v2;
}

std::vector<Node *> getAdjacentNodes(Node *currentNode, std::vector<std::vector<Node>> &heightMap) {
    std::vector<Node *> adjacentNodes = {};
    auto currentCoordinates = currentNode->coordinates;
    std::vector<Node *> candidates = {};
    if (currentCoordinates.first > 0) {
        candidates.push_back(&heightMap[currentCoordinates.first - 1][currentCoordinates.second]);
    }
    if (currentCoordinates.first < heightMap.size() - 1) {
        candidates.push_back(&heightMap[currentCoordinates.first + 1][currentCoordinates.second]);
    }
    if (currentCoordinates.second > 0) {
        candidates.push_back(&heightMap[currentCoordinates.first][currentCoordinates.second - 1]);
    }
    if (currentCoordinates.second < heightMap[currentCoordinates.first].size() - 1) {
        candidates.push_back(&heightMap[currentCoordinates.first][currentCoordinates.second + 1]);
    }
    for (auto &candidate: candidates) {
        if (!candidate->visited && candidate->height - currentNode->height <= 1) {
            adjacentNodes.push_back(candidate);
        }
    }
    return adjacentNodes;
}

int findShortestPathFrom(std::pair<int, int> start, std::pair<int, int> finish, std::vector<std::vector<Node>> heightMap) {
    std::pair<int, int> currentCoordinates = start;
    heightMap[start.first][start.second].shortestPath = 0;
    std::vector<Node *> toVisit = {};
    while (currentCoordinates != finish) {
        auto currentNode = &heightMap[currentCoordinates.first][currentCoordinates.second];
        if (currentNode->visited) {
            return INT_MAX;
        }
        auto adjacentNodes = getAdjacentNodes(currentNode, heightMap);
        auto distanceToAdjacent = currentNode->shortestPath + 1;
        for (auto &node: adjacentNodes) {
            if (node->shortestPath > distanceToAdjacent) {
                node->shortestPath = distanceToAdjacent;
                bool alreadyPresent = false;
                for (auto queuedNode: toVisit) {
                    if (queuedNode->coordinates == node->coordinates) {
                        alreadyPresent = true;
                    }
                }
                if (!alreadyPresent) {
                    toVisit.push_back(node);
                }
            }
        }
        currentNode->visited = true;
        currentCoordinates = (*std::min_element(toVisit.begin(), toVisit.end(), compareNodes))->coordinates;
    }
    return heightMap[currentCoordinates.first][currentCoordinates.second].shortestPath;
}

std::vector<std::vector<Node>> generateMinDistanceMap(std::pair<int, int> goal, std::vector<std::vector<Node>> &heightMap) {
  // make a map of min distances for each position
}

SolutionDay12::SolutionDay12(std::ifstream input) {
    std::pair<int, int> start = {};
    std::pair<int, int> finish = {};
    int lineNumber = 0;
    std::vector<std::vector<Node>> heightMap = {};
    for (std::string line; getline(input, line);) {
        std::vector<Node> row = {};
        for (int i = 0; i < line.size(); ++i) {
            auto value = line[i];
            auto coordinates = std::make_pair(lineNumber, i);
            if (value == 'S') {
                start = std::make_pair(lineNumber, i);
                row.emplace_back(0, coordinates);
            } else if (value == 'E') {
                finish = std::make_pair(lineNumber, i);
                row.emplace_back(25, coordinates);
            } else {
                row.emplace_back(value - 'a', coordinates);
            }
        }
        heightMap.push_back(row);
        lineNumber++;
    }
    shortestPathFromStart = findShortestPathFrom(start, finish, heightMap);
    for (int x = 0; x < heightMap.size(); ++x) {
        for (int y = 0; y < heightMap[x].size(); ++y) {
            auto currentNode = heightMap[x][y];
            if (currentNode.height == 0) {
                auto currentPath = findShortestPathFrom(std::make_pair(x,y), finish, heightMap);
                if (currentPath < shortestPathFromAnywhere) {
                    shortestPathFromAnywhere = currentPath;
                }
            }
        }
    }
}

int SolutionDay12::solve1() {
    return shortestPathFromStart;
}

int SolutionDay12::solve2() {
    return shortestPathFromAnywhere;
}
