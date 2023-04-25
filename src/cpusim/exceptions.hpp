#pragma once
#include <stdexcept>
#include <string>

class MatrixIndexOutOfRangeException : public std::out_of_range {
public:
    MatrixIndexOutOfRangeException(std::string&& message)
        : std::out_of_range(message) {}
};
