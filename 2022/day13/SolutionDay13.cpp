//
// Created by Augustin Grigorov on 13/12/2022.
//

#include "SolutionDay13.h"
#include <vector>
#include <stack>
#include <iostream>

struct PacketData {
    using List = std::vector<PacketData>;
    using Value = std::variant<int, List>;
    Value value;
};

bool operator<(const PacketData &p1, const PacketData &p2) {
    if (holds_alternative<int>(p1.value) && holds_alternative<int>(p2.value)){
        return get<int>(p1.value) < get<int>(p2.value);
    }
    if (holds_alternative<PacketData::List>(p1.value) && holds_alternative<PacketData::List>(p2.value)){
        return get<PacketData::List>(p1.value) < get<PacketData::List>(p2.value);
    }
    if (holds_alternative<int>(p1.value) && holds_alternative<PacketData::List>(p2.value)) {
        return PacketData::List {p1} < std::get<PacketData::List>(p2.value);
    }
    if (holds_alternative<PacketData::List>(p1.value) && holds_alternative<int>(p2.value)) {
        return get<PacketData::List>(p1.value) < PacketData::List {p2};
    }
    throw std::runtime_error("Unexpected comparison");
}

PacketData parseLine (std::ifstream &input) {
    std::string line;
    getline(input, line);
    PacketData topLevel;
    topLevel.value = PacketData::List {};
    std::stack<PacketData::List *> parents;
    PacketData::List * current = &std::get<PacketData::List>(topLevel.value);
    parents.push(current);
    std::string integerBeingParsed;
    for (auto c: line.substr(1)) {
        if (c >= '0' && c <= '9') {
            integerBeingParsed += c;
        } else {
            switch (c) {
                case '[': {
                    PacketData::List list = {};
                    current->emplace_back(PacketData{list});
                    parents.push(current);
                    current = &std::get<PacketData::List>(current->back().value);
                    break;
                }
                case ',':
                    if (!integerBeingParsed.empty()) {
                        current->push_back(PacketData{atoi(integerBeingParsed.c_str())});
                        integerBeingParsed.clear();
                    }
                    break;
                case ']':
                    if (!integerBeingParsed.empty()) {
                        current->push_back(PacketData{atoi(integerBeingParsed.c_str())});
                        integerBeingParsed.clear();
                    }
                    current = parents.top();
                    parents.pop();
                    break;
                default:
                    throw std::runtime_error("Unexpected input");
            }
        }
    }
    return topLevel;
}

SolutionDay13::SolutionDay13(std::ifstream input) {
    std::vector<std::pair<PacketData, PacketData>> signalPacketsPart1 = {};
    std::vector<PacketData> signalPacketsPart2 = {};
    while (input) {
        auto first = parseLine(input);
        auto second = parseLine(input);
        signalPacketsPart1.emplace_back(first, second);
        std::string discard;
        getline(input, discard);
        signalPacketsPart2.push_back(first);
        signalPacketsPart2.push_back(second);
    }
    for (int i = 0; i < signalPacketsPart1.size(); ++i) {
        auto &[leftPacket, rightPacket] = signalPacketsPart1[i];
        if (!(rightPacket < leftPacket)) {
            packetsInTheRightOrder += i + 1;
        }
    }
    auto firstMarker = PacketData{PacketData::List {PacketData::List {PacketData{2}}}};
    auto secondMarker = PacketData{PacketData::List {PacketData::List {PacketData{6}}}};
    signalPacketsPart2.push_back(firstMarker);
    signalPacketsPart2.push_back(secondMarker);
    std::sort(signalPacketsPart2.begin(), signalPacketsPart2.end());
    int index1 = 0;
    int index2 = 0;
    while (signalPacketsPart2[index1] < firstMarker) {
        index1++;
    }
    while (signalPacketsPart2[index2] < secondMarker) {
        index2++;
    }
    dividerProduct = (index1 + 1) * (index2 + 1);
}

int SolutionDay13::solve1() {
    return packetsInTheRightOrder;
}

int SolutionDay13::solve2() {
    return dividerProduct;
}
