#include "SolutionDay7.h"
#include <iostream>
#include <sstream>
#include <algorithm>


int hasFiveOfAKind(const std::vector<int> &handRepeats) {
    return !handRepeats.empty() && handRepeats[0] == 5;
}

bool hasFourOfAKind(const std::vector<int> &handRepeats) {
    return !handRepeats.empty() && handRepeats[0] == 4;
}

bool hasFullHouse(const std::vector<int> &handRepeats) {
    return handRepeats.size() >= 2 && handRepeats[0] == 3 && handRepeats[1] == 2;
}

bool hasThreeOfAKind(const std::vector<int> &handRepeats) {
    return !handRepeats.empty() && handRepeats[0] == 3;
}

bool hasTwoPair(const std::vector<int> &handRepeats) {
    return handRepeats.size() >= 2 && handRepeats[0] == 2 && handRepeats[1] == 2;
}

bool hasOnePair(const std::vector<int> &handRepeats) {
    return !handRepeats.empty() && handRepeats[0] == 2;
}

std::vector<int> getCardValues(const std::string& cards, bool useJokers) {
    std::vector<int> result = {};
    for (auto card : cards) {
        switch (card) {
            case 'T':
                result.push_back(10);
                break;
            case 'J':
                if (useJokers) {
                    result.push_back(1);
                } else {
                    result.push_back(11);
                }
                break;
            case 'Q':
                result.push_back(12);
                break;
            case 'K':
                result.push_back(13);
                break;
            case 'A':
                result.push_back(14);
                break;
            default:
                result.push_back(card - '0');
                break;
        }
    }
    return result;
}

std::vector<int> getRepeatedCardCounts(std::string &hand, bool useJokers) {
    std::vector<int> repeats = {};
    int index = 0;
    int currentStreak = 0;
    int jokers = 0;
    while (index < hand.size()) {
        if (useJokers && hand[index] == 'J') {
            jokers++;
            index++;
            continue;
        }
        if (index == 0) {
            index++;
            continue;
        }
        if (hand[index] == hand[index - 1]) {
            currentStreak++;
        } else {
            if (currentStreak > 0) repeats.push_back(currentStreak + 1);
            currentStreak = 0;
        }
        index++;
    }
    if (currentStreak > 0) repeats.push_back(currentStreak + 1);
    std::sort(repeats.begin(), repeats.end(), std::greater());
    if (useJokers) {
        if (!repeats.empty()) {
            repeats[0] += jokers;
        } else {
            if (jokers == 5) jokers--;
            repeats.push_back(jokers + 1);
        }
    }
    return repeats;
}

SolutionDay7::SolutionDay7(std::ifstream input) {
    std::vector<Hand> hands = {};
    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            std::istringstream is{line};
            std::string cards = {};
            int bet = 0;
            is >> cards;
            is >> bet;
            auto cardValues1 = getCardValues(cards, false);
            auto cardValues2 = getCardValues(cards, true);

            auto cardsForSorting = cards;
            std::sort(cardsForSorting.begin(), cardsForSorting.end());
//            auto repeatedCards1 = getRepeatedCardCounts(cardsForSorting, false);
            auto repeatedCards2 = getRepeatedCardCounts(cardsForSorting, true);

            int power1 = 0;
//            if (hasOnePair(repeatedCards1)) power1 = 1;
//            if (hasTwoPair(repeatedCards1)) power1 = 2;
//            if (hasThreeOfAKind(repeatedCards1)) power1 = 3;
//            if (hasFullHouse(repeatedCards1)) power1 = 4;
//            if (hasFourOfAKind(repeatedCards1)) power1 = 5;
//            if (hasFiveOfAKind(repeatedCards1)) power1 = 6;

            int power2 = 0;
            if (hasOnePair(repeatedCards2)) power2 = 1;
            if (hasTwoPair(repeatedCards2)) power2 = 2;
            if (hasThreeOfAKind(repeatedCards2)) power2 = 3;
            if (hasFullHouse(repeatedCards2)) power2 = 4;
            if (hasFourOfAKind(repeatedCards2)) power2 = 5;
            if (hasFiveOfAKind(repeatedCards2)) power2 = 6;

            hands.emplace_back(cards, power1, power2, bet, cardValues1, cardValues2);
        }
    }

//    std::sort(
//            std::begin(hands),
//            std::end(hands),
//            [](const auto &lhs, const auto &rhs) {
//                if (lhs.power1 == rhs.power1) {
//                    return lhs.cardValues1 < rhs.cardValues1;
//                } else {
//                    return lhs.power1 < rhs.power1;
//                }
//            });
//    for (int i = 0; i < hands.size(); ++i) {
//        std::cout << hands[i].cards << " " << hands[i].bet << "\n";
//        partOneSum += hands[i].bet * (i + 1);
//    }
    std::sort(
            std::begin(hands),
            std::end(hands),
            [](const auto &lhs, const auto &rhs) {
                if (lhs.power2 == rhs.power2) {
                    return lhs.cardValues2 < rhs.cardValues2;
                } else {
                    return lhs.power2 < rhs.power2;
                }
            });
    for (int i = 0; i < hands.size(); ++i) {
        std::cout << hands[i].cards << " " << hands[i].bet << "\n";
        partTwoSum += hands[i].bet * (i + 1);
    }
}

long SolutionDay7::solve1() const {
    return partOneSum;
}

int SolutionDay7::solve2() const {
    return partTwoSum;
}
