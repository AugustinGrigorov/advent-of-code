//
// Created by Augustin Grigorov on 16/12/2022.
//

#include "SolutionDay16.h"
#include "../util/Util.h"
#include <sstream>
#include <vector>
#include <unordered_map>
#include <iostream>

struct Valve {
public:
    Valve () {
        throw std::runtime_error("Should never happen");
    }
    explicit Valve (int rate) : rate(rate) {};
    int rate = 0;
    std::vector<Valve *> children = {};
};

void parseLine(
        std::string &input,
        std::unordered_map<std::string, Valve> &valveDictionary,
        std::unordered_map<std::string, std::vector<std::string>> &valveConnections
) {
    std::istringstream is{input};
    Util::discard(is, 1);
    std::string currentValveName;
    is >> currentValveName;
    Util::discard(is, 2);
    std::string rateRaw;
    is >> rateRaw;
    int rate = atoi(rateRaw.substr(5, rateRaw.size() -1).c_str());
    valveDictionary.emplace(currentValveName, rate);
    Util::discard(is, 4);

    std::string child;
    while (is && is >> child && !child.empty()) {
        valveConnections[currentValveName].push_back(child.substr(0, 2));
    }
}

SolutionDay16::SolutionDay16(std::ifstream input) {
    std::unordered_map<std::string, Valve> valveDictionary = {};
    std::unordered_map<std::string, std::vector<std::string>> valveConnections = {};
    for (std::string line; getline(input, line);) {
        parseLine(line, valveDictionary, valveConnections);
    }
    for (auto &[valveName, valve] : valveDictionary) {
        auto children = valveConnections[valveName];
        for (auto &child : children) {
            valve.children.push_back(&valveDictionary[child]);
        }
    }
}

int SolutionDay16::solve1() {
    return 0;
}

int SolutionDay16::solve2() {
    return 0;
}
