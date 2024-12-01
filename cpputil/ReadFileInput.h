//
// Created by Augustin Grigorov on 05/12/2022.
//

#ifndef CPPUTIL_READFILEINPUT_H
#define CPPUTIL_READFILEINPUT_H

#include <fstream>
#include <string>

class ReadFileInput {
public:
    static std::ifstream parseFile(std::string path);
};


#endif //CPPUTIL_READFILEINPUT_H
