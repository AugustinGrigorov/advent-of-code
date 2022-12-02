//
// Created by Augustin Grigorov on 02/12/2022.
//

#include "SolutionDay2.h"
#include <fstream>
#include <map>

std::map<char, int> inputToVal = {
        {'A', 1},
        {'B', 2},
        {'C', 3},
        {'X', 1},
        {'Y', 2},
        {'Z', 3}
};

int scoreRoundVariant1(int theirShape, int myShape) {
    switch (myShape) {
        case 1:
            switch (theirShape) {
                case 1:
                    return 4;
                case 2:
                    return 1;
                case 3:
                    return 7;
                default:
                    return 0;
            }
        case 2:
            switch (theirShape) {
                case 1:
                    return 8;
                case 2:
                    return 5;
                case 3:
                    return 2;
                default:
                    return 0;
            }
        case 3:
            switch (theirShape) {
                case 1:
                    return 3;
                case 2:
                    return 9;
                case 3:
                    return 6;
                default:
                    return 0;
            }
        default:
            return 0;
    }
}

int scoreRoundVariant2(int theirShape, int result) {
    switch (result) {
        case 1: // Need to lose
            switch (theirShape) {
                case 1:
                    return 3;
                case 2:
                    return 1;
                case 3:
                    return 2;
                default:
                    return 0;
            }
        case 2: // Need to draw
            switch (theirShape) {
                case 1:
                    return 4;
                case 2:
                    return 5;
                case 3:
                    return 6;
                default:
                    return 0;
            }
        case 3: // Need to win
            switch (theirShape) {
                case 1:
                    return 8;
                case 2:
                    return 9;
                case 3:
                    return 7;
                default:
                    return 0;
            }
        default:
            return 0;
    }
};

SolutionDay2::SolutionDay2() {
    std::string line;
    std::ifstream input;
    input.open("day2/input");
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    while (getline(input, line)) {
        if (!line.empty()) {
            int val1 = inputToVal[line[0]];
            int val2 = inputToVal[line[2]];
            score1 += scoreRoundVariant1(val1, val2);
            score2 += scoreRoundVariant2(val1, val2);
        }
    }
}

int SolutionDay2::solve1() {
    return score1;
}

int SolutionDay2::solve2() {
    return score2;
}