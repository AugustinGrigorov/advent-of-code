#include "SolutionDay2.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <unordered_map>

int firstItemThatFails(std::vector<int> &level) {
    if (level[0] == level[1]) return 0;
    bool isIncreasing = level[0] < level[1];
    for (int i = 1; i < level.size(); i++) {
        int current = level[i];
        int previous = level[i - 1];
        if (std::abs(current - previous) > 3) {
            return i;
        }
        if (current == previous) {
            return i;
        }
        if (current > previous && !isIncreasing) {
            return i;
        }
        if (current < previous && isIncreasing) {
            return i;
        }
    }
    return -1;
}

SolutionDay2::SolutionDay2(std::ifstream input)
{
    int lineNum = 0;
    for (std::string line; getline(input, line);)
    {
        lineNum++;
        if (!line.empty())
        {
            std::vector<int> level = {};
            std::istringstream stream(line);
            int nextNumber;
            while (stream >> nextNumber) {
                level.push_back(nextNumber);
            }
            int failAt = firstItemThatFails(level);
            if (failAt == -1) {
                partOneSol++;
                partTwoSol++;
            } else {
                 for (int i = 0; i < level.size(); i++) {
                    auto levelCopy = level;
                    levelCopy.erase(levelCopy.begin() + i);
                    if (firstItemThatFails(levelCopy) == -1) {
                        partTwoSol++;
                        break;
                    }
                }
            }
        }
    }
}



int SolutionDay2::solve1() const
{
    return partOneSol;
}

int SolutionDay2::solve2() const
{
    return partTwoSol;
}
