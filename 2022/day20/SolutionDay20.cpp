//
// Created by Augustin Grigorov on 20/12/2022.
//

#include "SolutionDay20.h"
#include <vector>
#include <iostream>

struct Node {
public:
    Node(int64_t value): value(value){};
    int64_t value;
    Node * left;
    Node * right;
};

//std::vector<std::shared_ptr<Node>> getListOrder(const std::shared_ptr<Node>& root){
//    std::vector<std::shared_ptr<Node>> order = {};
//    order.push_back(root);
//    std::shared_ptr<Node> current;
//    current = root->right;
//    while (current != root) {
//        order.push_back(current);
//        current = current->right;
//    }
//    return order;
//}

void runCycles(const std::vector<std::unique_ptr<Node>>& order, int numberOfCycles) {
    for (int i = 0; i < numberOfCycles; ++i) {
        for (const auto& node: order) {
            if(node->value == 0) {
                continue;
            }
            auto oldLeftNeighbour = node->left;
            auto oldRightNeighbour = node->right;
            Node * newLeftNeighbour = {};
            Node * newRightNeighbour = {};
            oldLeftNeighbour->right = oldRightNeighbour;
            oldRightNeighbour->left = oldLeftNeighbour;

            if (node->value > 0) {
                newLeftNeighbour = node.get();
            } else if (node->value < 0) {
                newRightNeighbour = node.get();
            }
            auto moveSize = abs(node->value) % (order.size() - 1);
            for (size_t j = 0; j < moveSize; ++j) {
                if (node->value > 0) {
                    newLeftNeighbour = newLeftNeighbour->right;
                } else if (node->value < 0) {
                    newRightNeighbour = newRightNeighbour->left;
                }
            }

            assert((newLeftNeighbour != nullptr || newRightNeighbour != nullptr) && (newLeftNeighbour == nullptr || newRightNeighbour == nullptr));
            if (newLeftNeighbour != nullptr) {
                newRightNeighbour = newLeftNeighbour->right;
            }
            if (newRightNeighbour != nullptr) {
                newLeftNeighbour = newRightNeighbour->left;
            }

            newLeftNeighbour->right = node.get();
            newRightNeighbour->left = node.get();
            node->left = newLeftNeighbour;
            node->right = newRightNeighbour;
        }
    }
}

std::pair<std::vector<std::unique_ptr<Node>>, Node *> generateNodes(std::vector<std::string> &lines, int64_t multiplier){
    std::vector<std::unique_ptr<Node>> order = {};
    std::unique_ptr<Node> root = std::make_unique<Node>(atoi(lines[0].c_str()) * multiplier);
    Node * current = root.get();
    order.push_back(std::move(root));
    Node * nodeZero=nullptr;
    for (size_t i = 1; i < lines.size(); ++i) {
        auto &line = lines[i];
        auto newNode = std::make_unique<Node>(atoi(line.c_str()) * multiplier);
        if (newNode->value == 0) {
            nodeZero = newNode.get();
        }
        current->right = newNode.get();
        newNode->left = current;
        current = newNode.get();
        order.push_back(std::move(newNode));
    }
    current->right = root.get();
    order[0]->left = current;
    return std::make_pair(std::move(order), nodeZero);
}

SolutionDay20::SolutionDay20(std::ifstream input) {
    std::vector<std::string> inputLines = {};
    for (std::string line; getline(input, line) && !line.empty();) {
        inputLines.push_back(line);
    }

    auto [orderPart1, nodeZeroPart1] = generateNodes(inputLines, 1);
    runCycles(orderPart1, 1);
    auto currentPart1 = nodeZeroPart1;

    auto [orderPart2, nodeZeroPart2] = generateNodes(inputLines, 811589153);
    runCycles(orderPart2, 10);
    auto currentPart2 = nodeZeroPart2;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 1000; ++j) {
            currentPart1 = currentPart1->right;
            currentPart2 = currentPart2->right;
        }
        sumOfCoordinates1 += currentPart1->value;
        sumOfCoordinates2 += currentPart2->value;
    }
}

int64_t SolutionDay20::solve1() {
    return sumOfCoordinates1;
}

int64_t SolutionDay20::solve2() {
    return sumOfCoordinates2;
}
