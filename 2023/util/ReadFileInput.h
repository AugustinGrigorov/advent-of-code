//
// Created by Augustin Grigorov on 05/12/2022.
//

#ifndef AOC2022_READFILEINPUT_H
#define AOC2022_READFILEINPUT_H

#include <fstream>
#include <string>

class ReadFileInput {
public:
    static std::ifstream parseFile(std::string path);
};


#endif //AOC2022_READFILEINPUT_H
