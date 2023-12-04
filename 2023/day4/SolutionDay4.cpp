#include "SolutionDay4.h"
#include <iostream>
#include <vector>
#include <set>
#include <cmath>
#include <numeric>

int scoreTicket (int matches) {
    return std::pow(2, matches - 1);
}

int calculateMatches (std::pair<std::vector<int>, std::set<int>> ticket) {
    int matches = 0;
    for (int number : ticket.first) {
        if (ticket.second.contains(number)) {
            matches++;
        }
    }
    return matches;
}

SolutionDay4::SolutionDay4(std::ifstream input)
{
    std::vector<std::pair<std::vector<int>, std::set<int>>> ticketVariations = {};
    std::vector<int> ticketScores;
    std::vector<int> ticketMatchingNumbers;
    std::vector<int> unevaluatedTickets;
    std::vector<int> totalTickets;

    for (std::string line; getline(input, line);)
    {
        std::vector<int> ticketNumbers = {};
        std::set<int> winningNumbers = {};
        if (!line.empty())
        {
            std::istringstream is{line};
            std::string discard;
            is >> discard;
            is >> discard;
            int nextInt = 0;
            while (is >> nextInt) {
                ticketNumbers.push_back(nextInt);
            }
            is.clear();
            is >> discard;
            while (is >> nextInt) {
                winningNumbers.insert(nextInt);
            }
            auto ticket = std::make_pair(ticketNumbers, winningNumbers);
            ticketVariations.push_back(ticket);
        }
    }

    for (auto ticket: ticketVariations) {
        int matches = calculateMatches(ticket);
        ticketMatchingNumbers.push_back(matches);
        ticketScores.push_back(scoreTicket(matches));
    }

    partOneSum = std::accumulate(ticketScores.begin(), ticketScores.end(), 0);

    unevaluatedTickets.assign(ticketVariations.size(), 1);
    totalTickets.assign(ticketVariations.size(), 1);

    for (int i = 0; i < unevaluatedTickets.size(); ++i) {
        int numberOfTicketsOfType = unevaluatedTickets[i];
        int ticketReward = ticketMatchingNumbers[i];
        for (int j = 1; j <= ticketReward; ++j) {
            totalTickets[i + j] += numberOfTicketsOfType;
            unevaluatedTickets[i + j] += numberOfTicketsOfType;
        }
    }

    partTwoSum += std::accumulate(totalTickets.begin(), totalTickets.end(), 0);
}

int SolutionDay4::solve1() const
{
    return partOneSum;
}

int SolutionDay4::solve2() const
{
    return partTwoSum;
}
