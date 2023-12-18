#include "SolutionDay18.h"
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>

std::pair<long, long> getNewCoordinates(
        std::pair<long, long> currentCoordinates,
        char direction,
        long distance
) {
    auto [x, y] = currentCoordinates;

    switch (direction) {
        case 'R':
        case '0':
            x += distance;
            break;
        case 'L':
        case '2':
            x -= distance;
            break;
        case 'U':
        case '3':
            y += distance;
            break;
        case 'D':
        case '1':
            y -= distance;
            break;
        default:
            throw std::invalid_argument("Unexpected direction");
    }

    return std::make_pair(x, y);
}

long getShoelaceArea(std::vector<std::pair<long, long>> vertices) {
    long area = 0;

    for (long i = 0; i < vertices.size() - 1; ++i) {
        area += vertices[i].first * vertices[i + 1].second - vertices[i + 1].first * vertices[i].second;
    }

    return std::abs(area) / 2;
}

struct ProblemState {
public:
    std::vector<std::pair<long, long>> vertices = {};
    std::pair<long, long> currentCoordinates = std::make_pair(0, 0);
    long totalDistance = 0;
};

void processInstruction(std::pair<char, long> &instruction, ProblemState &state) {
    auto direction = instruction.first;
    auto distance = instruction.second;
    state.totalDistance += distance;
    auto nextCoordinate = getNewCoordinates(state.currentCoordinates, direction, distance);
    state.vertices.push_back(nextCoordinate);
    state.currentCoordinates = nextCoordinate;
}

SolutionDay18::SolutionDay18(std::ifstream input) {
    ProblemState part1 = {};
    std::vector<std::pair<char, long>> instructionsPart1 = {};
    ProblemState part2 = {};
    std::vector<std::pair<char, long>> instructionsPart2 = {};

    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            char direction;
            long distance;
            std::string secondInstruction;

            std::istringstream is{line};

            // part 1
            is >> direction;
            is >> distance;
            instructionsPart1.emplace_back(direction, distance);

            // part 2
            is >> secondInstruction;
            instructionsPart2.emplace_back(
                    secondInstruction[secondInstruction.size() - 2],
                    std::stoi(secondInstruction.substr(2, 5), nullptr, 16)
            );
        }
    }

    for (int i = 0; i < instructionsPart1.size(); ++i) {
        processInstruction(instructionsPart1[i], part1);
        processInstruction(instructionsPart2[i], part2);
    }

    partOneSum = getShoelaceArea(part1.vertices) - part1.totalDistance / 2 + 1 + part1.totalDistance;
    partTwoSum = getShoelaceArea(part2.vertices) - part2.totalDistance / 2 + 1 + part2.totalDistance;
}

long SolutionDay18::solve1() const {
    return partOneSum;
}

long SolutionDay18::solve2() const {
    return partTwoSum;
}

