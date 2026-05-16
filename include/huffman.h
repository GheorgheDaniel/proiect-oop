#pragma once
#include <string>
#include <vector>
#include <cstdint>
#include "ICompressor.h"
#include "huffmantree.h"
#include "node.h"

class Huffman: public ICompressor{

    private: 
    HuffmanTree HT;
    public: 
    ~Huffman() override;
    void clearTree();
    void compress(const std::string& in, const std::string& out) override;
    void decompress(const std::string& in, const std::string& out, size_t alreadyread) override;
};