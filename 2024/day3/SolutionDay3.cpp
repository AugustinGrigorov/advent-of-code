#include "SolutionDay3.h"

#include <regex>
#include <ranges>
#include <iostream>
#include <sstream>

void progressUntilNumber (std::istringstream &stream) {
    char c;

    while (stream >> c) {
        if (std::isdigit(c)) {
            stream.putback(c);
            break;
        }
    }
}

SolutionDay3::SolutionDay3(std::ifstream input)
{
    std::regex pattern(R"((mul\([0-9]+,[0-9]+\))|(do\(\))|(don't\(\)))");
    bool instructionsEnabled = true;

    for (std::string line; getline(input, line);)
    {
        if (!line.empty())
        {
            std::smatch match;
            std::string::const_iterator searchStart(line.cbegin());
            while (regex_search(searchStart, line.cend(), match, pattern))
            {
                auto currentMatch = match[0];
                searchStart = match.suffix().first;

                if (match[0] == "do()") {
                  instructionsEnabled = true;
                  continue;
                }
                if (match[0] == "don't()") {
                  instructionsEnabled = false;
                  continue;
                }

                std::istringstream stream(currentMatch);
                int firstMultiple, secondMultiple;
                progressUntilNumber(stream);
                stream >> firstMultiple;
                progressUntilNumber(stream);
                stream >> secondMultiple;
                partOneSol += firstMultiple * secondMultiple;
                if (instructionsEnabled) {
                  partTwoSol += firstMultiple * secondMultiple;
                }
            }
        }
    }

}

int SolutionDay3::solve1() const
{
    return partOneSol;
}

int SolutionDay3::solve2() const
{
    return partTwoSol;
}
