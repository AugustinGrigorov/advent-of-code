//
// Created by Augustin Grigorov on 03/12/2022.
//

#include "SolutionDay3.h"
#include <array>
#include <unordered_set>

int letterPriority(char c) {
    if (islower(c)) {
        return c - 'a' + 1;
    } else {
        return c - 'A' + 27;
    }
}

SolutionDay3::SolutionDay3(std::ifstream input) {
    int lineNumber = 0;
    std::array<int, 52> badgeCandidateLetters = {};
    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            // Part 1
            bool usedLetters[52]{};
            std::string compartment1 = line.substr(0, line.size() / 2);
            std::string compartment2 = line.substr(line.size() / 2, line.size() / 2);
            for (char usedLetter: compartment1) {
                usedLetters[letterPriority(usedLetter) - 1] = true;
            }
            for (char repeatLetterCandidate: compartment2) {
                if (usedLetters[letterPriority(repeatLetterCandidate) - 1]) {
                    improperlyPlacedItems.push_back(repeatLetterCandidate);
                    break;
                }
            }
            // Part 2
            if (lineNumber % 3 == 0) {
                badgeCandidateLetters.fill(0);
            }
            std::unordered_set<char> uniqueChars(begin(line), end(line));
            for (char c: uniqueChars) {
                badgeCandidateLetters[letterPriority(c) - 1] += 1;
            }
            if (lineNumber % 3 == 2) {
                for (size_t i = 0; i < badgeCandidateLetters.size(); ++i) {
                    if (badgeCandidateLetters[i] == 3) {
                        badgeSum += i + 1;
                    }
                }
            }
            lineNumber++;
        }
    }
}

int SolutionDay3::solve1() {
    int sum = 0;
    for (char improperlyPlacedItem: improperlyPlacedItems) {
        sum += letterPriority(improperlyPlacedItem);
    }
    return sum;
}

int SolutionDay3::solve2() {
    return badgeSum;
}
