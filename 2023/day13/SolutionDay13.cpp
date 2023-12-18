#include "SolutionDay13.h"
#include <iostream>
#include <limits>
#include <vector>
#include <cassert>

int findIndexOfVerticalPattern(std::vector<std::string> &area, int mistakesAllowed, int previousDivider) {
    int width = area[0].size();
    int height = area.size();
    int indexToUse = -1;

    for (int col = 0; col < width - 1; ++col) {
        int remainingMistakes = mistakesAllowed;
        int colIndex1 = col;
        int colIndex2 = col + 1;
        while (colIndex1 >= 0 && colIndex2 < width && remainingMistakes > 0) {
            for (int row = 0; row < height; ++row) {
                if (area[row][colIndex1] != area[row][colIndex2]) {
                    remainingMistakes--;
                }
            }
            colIndex1--;
            colIndex2++;
        }
        if (remainingMistakes > 0 && col != previousDivider){
            indexToUse = col;
        }
    }
    return indexToUse;
}

int findIndexOfHorizontalPattern(std::vector<std::string> &area, int mistakesAllowed, int previousDivider) {
    int width = area[0].size();
    int height = area.size();
    int indexToUse = -1;

    for (int row = 0; row < height - 1; row++) {
        int remainingMistakes = mistakesAllowed;
        int rowIndex1 = row;
        int rowIndex2 = row + 1;

        while (rowIndex1 >= 0 && rowIndex2 < height && remainingMistakes > 0) {
            for (int col = 0; col < width; col++) {
                if (area[rowIndex1][col] != area[rowIndex2][col]) {
                    remainingMistakes--;
                }
            }
            rowIndex1--;
            rowIndex2++;
        }
        if (remainingMistakes > 0 && row != previousDivider) {
            indexToUse = row;
        }
    }
    return indexToUse;
}

SolutionDay13::SolutionDay13(std::ifstream input)
{
    std::vector<std::vector<std::string>> areas = {};
    std::vector<std::string> currentArea = {};

    for (std::string line; getline(input, line);)
    {
        if (!line.empty())
        {
            currentArea.push_back(line);
        } else {
            areas.push_back(currentArea);
            currentArea = {};
        }
    }
    areas.push_back(currentArea);

    std::vector<std::pair<int, int>> rowsAndColsInArea = {};
    for (auto area : areas) {
        int colsToLeft = findIndexOfVerticalPattern(area, 1, -1);
        int rowsAbove = findIndexOfHorizontalPattern(area, 1, -1);
        assert(colsToLeft == -1 || rowsAbove == -1);
        rowsAndColsInArea.emplace_back(rowsAbove, colsToLeft);
        if (colsToLeft >= 0) {
            partOneSum += colsToLeft + 1;
        }
        if (rowsAbove >= 0) {
            partOneSum += (rowsAbove + 1) * 100;
        }
    }

    for (int i = 0; i < areas.size(); ++i) {
        auto area = areas[i];
        int colsToLeft = findIndexOfVerticalPattern(area, 2, rowsAndColsInArea[i].second);
        int rowsAbove = findIndexOfHorizontalPattern(area, 2, rowsAndColsInArea[i].first);
        assert(rowsAbove != rowsAndColsInArea[i].first || colsToLeft != rowsAndColsInArea[i].second);

        if (colsToLeft != rowsAndColsInArea[i].second) {
            partTwoSum += colsToLeft + 1;
        }
        if (rowsAbove != rowsAndColsInArea[i].first) {
            partTwoSum += (rowsAbove + 1) * 100;
        }
    }
}

int SolutionDay13::solve1() const
{
    return partOneSum;
}

int SolutionDay13::solve2() const
{
    return partTwoSum;
}
