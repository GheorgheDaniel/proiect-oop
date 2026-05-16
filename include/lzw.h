#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "ICompressor.h"

class LZW: public ICompressor{

    public: 
    ~LZW() override;
    void compress(const std::string& in, const std::string& out) override;
    void decompress(const std::string& in, const std::string& out, size_t alreadyread) override;
};