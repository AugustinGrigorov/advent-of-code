#include "SolutionDay1.h"
#include <iostream>
#include <limits>

SolutionDay1::SolutionDay1(std::ifstream input)
{
    std::string digits[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    for (std::string line; getline(input, line);)
    {
        if (!line.empty())
        {
            // part 1
            int firstNumber = 0;
            int firstIndex = std::numeric_limits<int>::max();
            int secondNumber = 0;
            int secondIndex = 0;
            int nextNumber = 0;
            for (int i = 0; i < line.size(); ++i)
            {
                char nextChar = line[i];
                if (isdigit(nextChar))
                {
                    nextNumber = nextChar - '0';
                }
                if (nextNumber != 0)
                {
                    if (firstNumber == 0)
                    {
                        firstNumber = nextNumber;
                        firstIndex = i;
                    }
                    secondNumber = nextNumber;
                    secondIndex = i;
                    nextNumber = 0;
                }
            }
            partOneSum += firstNumber * 10 + secondNumber;

            // part 2
            for (int i = 0; i < 9; ++i)
            {
                std::string digit = digits[i];
                size_t index = line.find(digit);
                while (index != std::string::npos)
                {
                    if (index < firstIndex)
                    {
                        firstNumber = i + 1;
                        firstIndex = static_cast<int>(index);
                    }
                    if (index > secondIndex)
                    {
                        secondNumber = i + 1;
                        secondIndex = static_cast<int>(index);
                    }
                    index = line.find(digit, index + 1);
                }
            }
            partTwoSum += firstNumber * 10 + secondNumber;
        }
    }
}

int SolutionDay1::solve1() const
{
    return partOneSum;
}

int SolutionDay1::solve2() const
{
    return partTwoSum;
}
