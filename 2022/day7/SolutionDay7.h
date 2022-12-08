//
// Created by Augustin Grigorov on 07/12/2022.
//

#ifndef AOC2022_DAY7_H
#define AOC2022_DAY7_H

#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <sstream>
#include <utility>

class Folder {
public:
    Folder *parent;

    Folder() {
        parent = nullptr;
    };

    explicit Folder(Folder *parentToAdd) {
        parent = parentToAdd;
    };

    void addChild(const std::string &name, std::unique_ptr<Folder> f) {
        children[name] = std::move(f);
    };

    void addFileSize(long fileSize) {
        sizeOfFiles += fileSize;
    };

    Folder &getChild(const std::string &childName) {
        return *children[childName];
    };

    long getSize() {
        long totalSize = sizeOfFiles;
        for (const auto &child: children) {
            totalSize += child.second->getSize();
        }
        return totalSize;
    };
private:
    std::unordered_map<std::string, std::unique_ptr<Folder>> children;
    long sizeOfFiles = 0;
};

class SolutionDay7 {
public:
    explicit SolutionDay7(std::ifstream input);

    long solve1();

    long solve2();

private:
    Folder root;
    std::vector<Folder *> allFolders = {};
};


#endif //AOC2022_DAY7_H
