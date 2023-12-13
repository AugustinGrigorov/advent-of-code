#include "SolutionDay11.h"
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <deque>

long getDistance (int yDistance, int emptyRowsBetween, int xDistance, int emptyColsBetween, int multiplier) {
    return yDistance - emptyRowsBetween + emptyRowsBetween * multiplier + xDistance - emptyColsBetween + emptyColsBetween * multiplier;
}

SolutionDay11::SolutionDay11(std::ifstream input) {
    std::vector<std::string> problemSpace = {};
    std::deque<std::pair<int, int>> starsToCompare;
    std::vector<int> emptyRows = {};
    std::vector<int> emptyCols = {};
    for (std::string line; getline(input, line);) {
        problemSpace.push_back(line);
    }

    for (int i = 0; i < problemSpace.size(); ++i) {
        auto row = problemSpace[i];
        auto currentPos = row.begin();
        std::vector<std::pair<int, int>> starsOnThisRow = {};
        while (currentPos != row.end()) {
            currentPos = std::find(currentPos, row.end(), '#');
            if (currentPos != row.end()) {
                starsOnThisRow.emplace_back(i, std::distance(row.begin(), currentPos));
                currentPos++;
            }
        }
        if (!starsOnThisRow.empty()) {
            starsToCompare.insert(starsToCompare.end(), starsOnThisRow.begin(), starsOnThisRow.end());
        } else {
            emptyRows.push_back(i);
        }
    }
    for (int i = 0; i < problemSpace[0].size(); ++i) {
        bool isEmptyCol = true;
        for (auto row : problemSpace) {
            if (row[i] != '.') {
                isEmptyCol = false;
            }
        }
        if (isEmptyCol) {
            emptyCols.push_back(i);
        }
    }
    while (!starsToCompare.empty()) {
        auto nextStar = starsToCompare.front();
        starsToCompare.pop_front();
        for (auto star : starsToCompare) {
            int yCoordinates[2] = {nextStar.first, star.first};
            int xCoordinates[2] = {nextStar.second, star.second};
            std::sort(std::begin(yCoordinates), std::end(yCoordinates));
            std::sort(std::begin(xCoordinates), std::end(xCoordinates));
            int yDistance = yCoordinates[1] - yCoordinates[0];
            int xDistance = xCoordinates[1] - xCoordinates[0];
            int emptyRowsBetween = 0;
            int emptyColsBetween = 0;
            for (int rowIndex : emptyRows) {
                if (rowIndex > yCoordinates[0] && rowIndex < yCoordinates[1]) emptyRowsBetween++;
            }
            for (int colIndex : emptyCols) {
                if (colIndex > xCoordinates[0] && colIndex < xCoordinates[1]) emptyColsBetween++;
            }
            partOneSum += getDistance(yDistance, emptyRowsBetween, xDistance, emptyColsBetween, 2);
            partTwoSum += getDistance(yDistance, emptyRowsBetween, xDistance, emptyColsBetween, 1000000);
        }
    }
}

long SolutionDay11::solve1() const {
    return partOneSum;
}

long SolutionDay11::solve2() const {
    return partTwoSum;
}
