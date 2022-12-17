//
// Created by Augustin Grigorov on 15/12/2022.
//

#include "SolutionDay15.h"
#include <sstream>
#include <utility>
#include <vector>
#include <unordered_map>
#include <iostream>
#include "../util/Util.h"

class IntPairHash {
public:
    size_t operator()(std::pair<int, int> pair) const {
        std::hash<int> hash = {};
        auto hashProduct = hash(pair.first);
        hashProduct ^= hash(pair.second) + 0x517cc1b727220a95 + (hashProduct << 6) + (hashProduct >> 2);
        return hashProduct;
    }
};

std::pair<std::pair<int, int>, std::pair<int, int>> parseLine(std::string &input) {
    std::istringstream is{input};
    std::string rawSensorX;
    std::string rawSensorY;
    std::string rawBeaconX;
    std::string rawBeaconY;
    Util::discard(is, 2);
    is >> rawSensorX;
    is >> rawSensorY;
    Util::discard(is, 4);
    is >> rawBeaconX;
    is >> rawBeaconY;
    int sensorX = atoi(rawSensorX.substr(2, rawSensorX.size() - 1).c_str());
    int sensorY = atoi(rawSensorY.substr(2, rawSensorY.size() - 1).c_str());
    int beaconX = atoi(rawBeaconX.substr(2, rawBeaconX.size() - 1).c_str());
    int beaconY = atoi(rawBeaconY.substr(2, rawBeaconY.size()).c_str());
    return std::make_pair(std::make_pair(sensorX, sensorY), std::make_pair(beaconX, beaconY));
}

int calculateManhattanDistance(std::pair<int, int> p1, std::pair<int, int> p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}

void addToMap(
        std::pair<std::pair<int, int>, std::pair<int, int>> &sensorBeaconPair,
        std::unordered_map<std::pair<int, int>, char, IntPairHash> &map,
        int &lowerBoundX,
        int &upperBoundX,
        int desiredLine
) {
    auto [sensor, beacon] = sensorBeaconPair;
    map[sensor] = 'S';
    map[beacon] = 'B';


    auto distanceBetweenBeaconAndSensor = calculateManhattanDistance(sensor, beacon);
    auto distanceBetweenCurrentAndSensor = abs(sensor.second - desiredLine);

    if (distanceBetweenCurrentAndSensor > distanceBetweenBeaconAndSensor) {
        return;
    }

    if (sensor.first + distanceBetweenBeaconAndSensor > upperBoundX) {
        upperBoundX = sensor.first + distanceBetweenBeaconAndSensor;
    }
    if (sensor.first - distanceBetweenBeaconAndSensor < lowerBoundX) {
        lowerBoundX = sensor.first - distanceBetweenBeaconAndSensor;
    }

    auto radius = distanceBetweenBeaconAndSensor - distanceBetweenCurrentAndSensor;
    for (int x = sensor.first - radius; x <= sensor.first + radius; ++x) {
        auto currentPoint = std::make_pair(x, desiredLine);
        if (!map.contains(currentPoint)) {
            map[currentPoint] = '#';
        }
    }
}

SolutionDay15::SolutionDay15(std::ifstream input) {
    int desiredLine = 2000000;
    std::unordered_map<std::pair<int, int>, char, IntPairHash> caveMap = {};
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> sensorBeaconPairs = {};
    for (std::string line; getline(input, line);) {
        auto sensorBeaconPair = parseLine(line);
        sensorBeaconPairs.push_back(sensorBeaconPair);
//        addToMap(sensorBeaconPair, caveMap, lowerBoundX, upperBoundX, desiredLine);
    }
    for (int x = lowerBoundX - 1; x < upperBoundX + 1; ++x) {
        auto potentialPos = std::make_pair(x, desiredLine);
        if (caveMap[potentialPos] == '#' || caveMap[potentialPos] == 'S') {
            spotsWhereBeaconCannotBe++;
        }
    }
    // Part 2
//    std::unordered_map<std::pair<int, int>, char, IntPairHash> borderMap = {};
    int initialDimension = 4000000;
    std::vector<int> topBorder = {};
    std::vector<int> leftBorder = {};
    std::vector<int> rightBorder = {};
    std::vector<int> bottomBorder = {};
    for (int i = 0; i < initialDimension; ++i) {
        topBorder.push_back(0);
        leftBorder.push_back(0);
        rightBorder.push_back(initialDimension);
        bottomBorder.push_back(initialDimension);
    }
    //sort array
//    for (auto sensorBeaconPair : sensorBeaconPairs) {
//        auto [sensor, beacon] = sensorBeaconPair;
//        auto manhattanDistance = calculateManhattanDistance(sensor, beacon);
//
//        // find edges, reduce the size of the border
//    }
}

int SolutionDay15::solve1() {
    return spotsWhereBeaconCannotBe;
}

int SolutionDay15::solve2() {
    return 0;
}
