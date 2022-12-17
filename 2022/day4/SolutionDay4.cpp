//
// Created by Augustin Grigorov on 04/12/2022.
//

#include "SolutionDay4.h"

SolutionDay4::SolutionDay4(std::ifstream input) {
    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            long shifts[4] = {};
            char *workingInput = line.data();
            for (long &number: shifts) {
                number = strtol(workingInput, &workingInput, 10);
                workingInput++;
            }
            if ((shifts[0] <= shifts[2] && shifts[1] >= shifts[3]) || (shifts[0] >= shifts[2] && shifts[1] <= shifts[3])) {
                totalOverlapOccurrences++;
                partialOverlapOccurrences++;
                continue;
            }
            if ((shifts[0] >= shifts[2] && shifts[0] <= shifts[3]) || (shifts[1] >= shifts[2] && shifts[1] <= shifts[3])) {
                partialOverlapOccurrences++;
            }
        }
    }
}

int SolutionDay4::solve1() {
    return totalOverlapOccurrences;
}

int SolutionDay4::solve2() {
    return partialOverlapOccurrences;
}
