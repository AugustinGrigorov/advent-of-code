#include "SolutionDay9.h"
#include <iostream>
#include <vector>
#include <numeric>

SolutionDay9::SolutionDay9(std::ifstream input)
{
    for (std::string line; getline(input, line);)
    {
        std::vector<std::vector<long>> subSequences = {};
        std::vector<long> sequence = {};

        if (!line.empty())
        {
            std::istringstream is{line};
            long nextNum = 0;
            while (is >> nextNum) {
                sequence.push_back(nextNum);
            }
        }
        subSequences.push_back(sequence);
        for (int i = 0; i < subSequences.size(); ++i) {
            std::vector<long> nextSequence = {};
            auto currentSequence = subSequences[i];
            for (int j = 1; j < currentSequence.size(); ++j) {
                nextSequence.push_back(currentSequence[j] - currentSequence[j - 1]);
            }
            long firstChar = currentSequence[0];
            bool allEqual = true;
            for (long number : currentSequence) {
                if (number != firstChar)  {
                    allEqual = false;
                }
            }
            if (!allEqual) {
                subSequences.push_back(nextSequence);
            }
        }
        for (auto currentSequence : subSequences) {
            partOneSum += currentSequence[currentSequence.size() - 1];

        }

        long firstNumber = 0;
        for (int i = subSequences.size() - 1; i >= 0 ; --i) {
            firstNumber = subSequences[i][0] - firstNumber;
        }
        partTwoSum += firstNumber;
    }


}

long SolutionDay9::solve1() const
{
    return partOneSum;
}

long SolutionDay9::solve2() const
{
    return partTwoSum;
}
