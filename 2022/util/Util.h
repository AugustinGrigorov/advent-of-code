//
// Created by Augustin Grigorov on 05/12/2022.
//

#ifndef AOC2022_UTIL_H
#define AOC2022_UTIL_H

#include <fstream>
#include <string>

class Util {
public:
    static std::ifstream parseFile(std::string path);
    static void discard(std::istringstream &is, int times);
};


#endif //AOC2022_UTIL_H
