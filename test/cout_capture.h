#pragma once

#include <iostream>
#include <sstream>
#include <string>

class CoutCapture {
public:
    CoutCapture() : oldBuf(std::cout.rdbuf(ss.rdbuf())) {};
    ~CoutCapture() {
        std::cout.rdbuf(oldBuf);
    }

    std::string str() const {
        return ss.str();
    }

private:
    std::stringstream ss;
    std::streambuf* oldBuf;
};
