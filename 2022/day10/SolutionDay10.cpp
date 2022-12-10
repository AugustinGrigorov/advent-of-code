//
// Created by Augustin Grigorov on 10/12/2022.
//

#include "SolutionDay10.h"
#include <sstream>

void saveSignalStrengthIfCorrectCycle(
        int cycles,
        int regX,
        int &signalStrength
) {
    if (cycles % 20 == 0 && (cycles / 20) % 2 == 1) {
        signalStrength += cycles * regX;
    }
}

void writeToOutput(
        int cycles,
        int regX,
        std::string &output
) {
    int position = (cycles - 1) % 40;
    if (position >= regX - 1 && position <= regX + 1) {
        output += '#';
    } else {
        output += '.';
    }
    if (position == 39) {
        output += "\n";
    }
}

void processCommand(
        std::string &command,
        int value,
        int &cycles,
        int &regX,
        int &signalStrength,
        std::string &output
) {
    saveSignalStrengthIfCorrectCycle(cycles, regX, signalStrength);
    writeToOutput(cycles, regX, output);
    cycles++;
    if (command == "addx") {
        saveSignalStrengthIfCorrectCycle(cycles, regX, signalStrength);
        writeToOutput(cycles, regX, output);
        regX += value;
        cycles++;
    }
}

SolutionDay10::SolutionDay10(std::ifstream input) {
    for (std::string line; getline(input, line);) {
        std::istringstream is{line};
        std::string command;
        is >> command;
        int value = 0;
        is >> value;
        processCommand(command, value, cycles, regX, signalStrength, output);
    }
}

int SolutionDay10::solve1() {
    return signalStrength;
}

std::string SolutionDay10::solve2() {
    return output;
}
