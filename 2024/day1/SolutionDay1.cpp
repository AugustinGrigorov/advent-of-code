#include "SolutionDay1.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>

SolutionDay1::SolutionDay1(std::ifstream input)
{
    std::vector<int> firstColumn = {};
    std::vector<int> secondColumn = {};
    std::unordered_map<int, int> secondColumnNumberOccurrence = {};

    for (std::string line; getline(input, line);)
    {
        if (!line.empty())
        {
            std::istringstream stream(line);
            int firstNumber, secondNumber;
            stream >> firstNumber >> secondNumber;
            firstColumn.push_back(firstNumber);
            secondColumn.push_back(secondNumber);
            if (secondColumnNumberOccurrence.find(secondNumber) != secondColumnNumberOccurrence.end()) {
              secondColumnNumberOccurrence[secondNumber]++;
            } else {
              secondColumnNumberOccurrence[secondNumber] = 1;
            }
        }
    }
    std::sort(firstColumn.begin(), firstColumn.end());
    std::sort(secondColumn.begin(), secondColumn.end());
    for (int i = 0; i < firstColumn.size(); i++) {
      partOneSol += std::abs(firstColumn[i] - secondColumn[i]);
    }
    for (int i = 0; i < firstColumn.size(); i++) {
        partTwoSol += firstColumn[i] * secondColumnNumberOccurrence[firstColumn[i]];
    }
}

int SolutionDay1::solve1() const
{
    return partOneSol;
}

int SolutionDay1::solve2() const
{
    return partTwoSol;
}
