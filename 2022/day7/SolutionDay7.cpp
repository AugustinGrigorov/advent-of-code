//
// Created by Augustin Grigorov on 07/12/2022.
//

#include "SolutionDay7.h"

SolutionDay7::SolutionDay7(std::ifstream input) {
    Folder *current = &root;
    allFolders.push_back(&root);
    for (std::string line; getline(input, line);) {
        std::istringstream is{line};
        std::string next;
        is >> next;
        if (next == "$") {
            is >> next;
            if (next == "cd") {
                is >> next;
                if (next == "/") {
                    current = &root;
                } else if (next == "..") {
                    current = current->parent;
                } else {
                    current = &current->getChild(next);
                }
            }
        } else {
            if (next == "dir") {
                is >> next;
                auto child = std::make_unique<Folder>(current);
                allFolders.push_back(child.get());
                current->addChild(next, std::move(child));
            } else {
                long fileSize = std::stol(next);
                current->addFileSize(fileSize);
            }
        }
    }
}

long SolutionDay7::solve1() {
    long sum = 0;
    for (auto folder: allFolders) {
        long folderSize = folder->getSize();
        if (folderSize < 100000) {
            sum += folderSize;
        }
    }
    return sum;
}

long SolutionDay7::solve2() {
    long freeSpace = 70000000 - root.getSize();
    long neededToFree = 30000000 - freeSpace;
    long smallestFolder = LLONG_MAX;
    for (auto folder: allFolders) {
        long folderSize = folder->getSize();
        if (folderSize > neededToFree && folderSize < smallestFolder) {
            smallestFolder = folderSize;
        }
    }
    return smallestFolder;
}
