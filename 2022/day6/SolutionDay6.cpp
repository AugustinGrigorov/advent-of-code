//
// Created by Augustin Grigorov on 06/12/2022.
//

#include "SolutionDay6.h"
#include <unordered_set>

int findFirstOccurrenceOfAUniqueSequenceOfChars(size_t numberOfUniqueCharsNeeded, const std::string& input) {
    for (size_t i = numberOfUniqueCharsNeeded - 1; i < input.size(); ++i) {
        std::string lastSegment = input.substr(i- (numberOfUniqueCharsNeeded - 1), numberOfUniqueCharsNeeded);
        std::unordered_set<char> uniqueCharactersInSequence(std::begin(lastSegment), std::end(lastSegment));
        if (uniqueCharactersInSequence.size() == numberOfUniqueCharsNeeded) {
            return i + 1;
        }
    }
    return 0;
}

SolutionDay6::SolutionDay6(std::ifstream input) {
    std::string line;
    getline(input, line);
    positionOfStartOfPacketMarker = findFirstOccurrenceOfAUniqueSequenceOfChars(4, line);
    positionOfStartOfMessageMarker = findFirstOccurrenceOfAUniqueSequenceOfChars(14, line);
}

int SolutionDay6::solve1() {
    return positionOfStartOfPacketMarker;
}

int SolutionDay6::solve2() {
    return positionOfStartOfMessageMarker;
}
