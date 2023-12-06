#include "SolutionDay6.h"
#include <iostream>
#include <limits>
#include <vector>
#include <sstream>

long combine(long a, long b) {
    long times = 1;
    while (times <= b)
        times *= 10;
    return a*times + b;
}

long findWaysOfWinningPerRace(long time, long distance) {
    long waysOfWinningPerRace = 0;
    for (int j = 0; j < time; ++j) {
        long remainder = time - j;
        long currentDistance = remainder * j;
        if (currentDistance > distance) {
            waysOfWinningPerRace = time + 1 - j * 2;
            break;
        }
    }
    return waysOfWinningPerRace;
}

SolutionDay6::SolutionDay6(std::ifstream input)
{
    int lineIndex = 0;
    std::vector<int> times = {};
    std::vector<int> distances = {};

    for (std::string line; getline(input, line);)
    {
        std::string discard;

        if (!line.empty())
        {
            std::istringstream is{line};
            is >> discard;
            int nextInt = 0;
            while (is >> nextInt) {
                switch (lineIndex) {
                    case 0:
                        times.push_back(nextInt);
                        break;
                    case 1:
                        distances.push_back(nextInt);
                        break;
                    default:
                        return;
                }
            }
            lineIndex++;
        }
    }

    for (int i = 0; i < times.size(); ++i) {
        waysOfWinningPerRaceProduct *= findWaysOfWinningPerRace(times[i], distances[i]);
    }

    long totalTime = times[0];
    long totalDistance = distances[0];
    for (int i = 1; i < times.size(); ++i) {
        totalTime = combine(totalTime, times[i]);
        totalDistance = combine(totalDistance, distances[i]);
    }
    waysOfWinningBigRace = findWaysOfWinningPerRace(totalTime, totalDistance);
}

long SolutionDay6::solve1() const
{
    return waysOfWinningPerRaceProduct;
}

long SolutionDay6::solve2() const
{
    return waysOfWinningBigRace;
}
