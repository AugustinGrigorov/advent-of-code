//
// Created by Augustin Grigorov on 05/12/2022.
//

#include "Util.h"
#include <fstream>
#include <sstream>

std::ifstream Util::parseFile(std::string path) {
    std::string line;
    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    return input;
}

void Util::discard(std::istringstream &is, int times) {
    std::string discard;
    for (int i = 0; i < times; ++i) {
        is >> discard;
    }
}
