//
// Created by Augustin Grigorov on 05/12/2022.
//

#include "ReadFileInput.h"
#include <fstream>


std::ifstream ReadFileInput::parseFile(std::string path) {
    std::string line;
    std::ifstream input;
    input.open(path);
    if (!input.is_open()) {
        throw std::runtime_error("Unable to open file");
    }
    return input;
}
