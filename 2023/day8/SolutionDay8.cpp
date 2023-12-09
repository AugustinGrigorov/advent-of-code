#include "SolutionDay8.h"
#include <iostream>
#include <limits>
#include <sstream>
#include <unordered_map>
#include <regex>
#include <numeric>

int traverse(int part, std::string path, Node* currentNode) {
    int steps = 0;
    while ((part == 1 && currentNode->name != "ZZZ") ||
           (part == 2 && currentNode->name[currentNode->name.length() - 1] != 'Z')) {
        switch (path[steps % path.length()]) {
            case 'L':
                currentNode = currentNode->left;
                break;
            case 'R':
                currentNode = currentNode->right;
                break;
        }
        steps++;
    }
    return steps;
}

SolutionDay8::SolutionDay8(std::ifstream input) {
    std::unordered_map<std::string, Node> nameToNode = {};
    std::string path;
    std::string discard;
    std::regex sanitizationRegex(R"(\(|\)|\,)");

    bool parsedPath = false;
    for (std::string line; getline(input, line);) {
        if (!line.empty()) {
            if (!parsedPath) {
                path = line;
                parsedPath = true;
                continue;
            }
            std::istringstream is{line};
            std::string root;
            std::string left;
            std::string right;
            is >> root;
            is >> discard;
            is >> left;
            is >> right;

            while (left != std::regex_replace(left, sanitizationRegex, "")) {
                left = std::regex_replace(left, sanitizationRegex, "");
            }

            while (right != std::regex_replace(right, sanitizationRegex, "")) {
                right = std::regex_replace(right, sanitizationRegex, "");
            }

            nameToNode[root].name = root;
            nameToNode[root].left = &nameToNode[left];
            nameToNode[root].right = &nameToNode[right];
        }
    }


    partOneSum = traverse(1, path, &nameToNode["AAA"]);

    std::vector<std::string> entryNodes = {};
    std::vector<int> cycles = {};
    for (const auto &entry: nameToNode) {
        if (entry.first[entry.first.length() - 1] == 'A') {
            entryNodes.push_back(entry.first);
        }
    }
    for (const auto& nodeName: entryNodes)
        cycles.push_back(traverse(2, path, &nameToNode[nodeName]));

    partTwoSum = std::accumulate(cycles.begin(), cycles.end(), 1L, [](long a, long b){
        return std::lcm(a, b);
    });

}

int SolutionDay8::solve1() const {
    return partOneSum;
}

long SolutionDay8::solve2() const {
    return partTwoSum;
}
