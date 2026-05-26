#pragma once
#include <string>


class ICompressor{
    public:
    virtual ~ICompressor() = default;
    
    virtual void compress(const std::string& inputFilePath, const std::string& outputFilePath, const int password) = 0;
    virtual void decompress(const std::string& inputFilePath, const std::string&outputFilePath, size_t alreadyread, const int password) = 0;
};


