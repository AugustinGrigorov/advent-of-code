#include "SolutionDay12.h"
#include <iostream>
#include <sstream>
#include <vector>

bool isValidRepresentation (std::string &representation, std::vector<int> &validator) {
    std::vector<int> damagedSpringCounts = {};
    int streak = 0;
    for (char c : representation)
    {
        if (c == '#') {
            streak++;
        } else {
            damagedSpringCounts.push_back(streak);
            streak = 0;
        }
    }
    return damagedSpringCounts == validator;
}

std::vector<std::string> generateAllPossibleCombinations (std::string &damagedRepresentation) {
    std::vector<std::string> allRepresentations = {""};
    for (char c : damagedRepresentation) {
        if (c == '?') {
            std::vector<std::string> newRepresentations;
            for (std::string const partialRepresentation : allRepresentations) {
                newRepresentations.push_back(partialRepresentation + '#');
                newRepresentations.push_back(partialRepresentation + '.');
            }
            allRepresentations = newRepresentations;
        } else {
            for (std::string &partialRepresentation : allRepresentations) {
                partialRepresentation += c;
            }
        }
    }
    return allRepresentations;
}

SolutionDay12::SolutionDay12(std::ifstream input)
{
    std::vector<std::pair<std::string, std::vector<int>>> conditionRecords = {};
    char discard = {};
    for (std::string line; getline(input, line);)
    {
        if (!line.empty())
        {
            std::istringstream is{line};
            std::vector<int> validator = {};
            
            std::string representation;
            int springGroup = 0;

            is >> representation;
            while (is >> springGroup)
            {
                validator.push_back(springGroup);
                is >> discard;
            }
            conditionRecords.emplace_back(representation, validator);
        }
    }
    for (auto record: conditionRecords) {
        auto allPossibleCombinations = generateAllPossibleCombinations(record.first);
        for (auto representation : allPossibleCombinations) {
            if (isValidRepresentation(representation, record.second)) partOneSum += 1;
        }
    }
}

int SolutionDay12::solve1() const
{
    return partOneSum;
}

int SolutionDay12::solve2() const
{
    return partTwoSum;
}
