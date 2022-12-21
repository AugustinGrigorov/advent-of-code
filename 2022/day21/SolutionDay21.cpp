//
// Created by Augustin Grigorov on 20/12/2022.
//

#include "SolutionDay21.h"
#include <sstream>
#include <vector>
#include <iostream>
#include <unordered_map>

namespace {
    struct Node {
    public:
        Node() {};
        int64_t value = 0;
        std::string child1Name;
        std::string child2Name;
        Node * child1 = nullptr;
        Node * child2 = nullptr;
        char operation = 0;
    };
}

SolutionDay21::SolutionDay21(std::ifstream input) {
    std::unordered_map<std::string, std::unique_ptr<Node>> nodeRegistry = {};
    for (std::string line; getline(input, line) && !line.empty();) {
        auto newNode = std::make_unique<Node>();
        std::string next;
        std::vector<std::string> instructions = {};
        for (std::istringstream is {line}; is >> next && !next.empty();) {
            instructions.push_back(next);
        }
        assert(instructions.size() == 2 || instructions.size() == 4);
        auto name = instructions[0].substr(0, instructions[0].size() - 1);
        if (instructions.size() == 2) {
            auto value = atoi(instructions[1].c_str());
            assert(value != 0);
            newNode->value = value;
        }
        if (instructions.size() == 4) {
            newNode->child1Name = instructions[1];
            assert(instructions[2].size() == 1);
            newNode->operation = instructions[2][0];
            newNode->child2Name = instructions[3];
        }
        nodeRegistry.emplace(name, std::move(newNode));
    }

    for (auto &entry : nodeRegistry) {
        auto node = entry.second.get();
        if (!node->child1Name.empty() && !node->child2Name.empty()) {
            node->child1 = nodeRegistry[node->child1Name].get();
            node->child2 = nodeRegistry[node->child2Name].get();
        }
    }
    auto hasUncomputedElements = true;
    while (hasUncomputedElements) {
        hasUncomputedElements = false;
        for (auto &entry : nodeRegistry) {
            auto node = entry.second.get();
            if (node->value == 0) {
                hasUncomputedElements = true;
                auto child1Value = node->child1->value;
                auto child2Value = node->child2->value;
                if (child1Value != 0 && child2Value != 0) {
                    switch (node->operation) {
                        case '+':
                            node->value = child1Value + child2Value;
                            break;
                        case '-':
                            node->value = child1Value - child2Value;
                            break;
                        case '*':
                            node->value = child1Value * child2Value;
                            break;
                        case '/':
                            node->value = child1Value / child2Value;
                            break;
                    }
                }
            }
        }
    }
    puzzlePart1 = nodeRegistry["root"]->value;
}

int64_t SolutionDay21::solve1() {
    return puzzlePart1;
}

int64_t SolutionDay21::solve2() {
    return 0;
}
