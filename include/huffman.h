#pragma once
#include <string>
#include <vector>
#include "ICompressor.h"

class Huffman: public ICompressor{
    private: 
    struct Node{
        Node *left, *right;
        int val;
        Node() {
            left = nullptr; right = nullptr;
        }
    };
    
    struct pii{
        int fr;
        uint8_t label;
        Node *nd;
        bool operator <(const pii& v) const{
            return this->fr > v.fr;
        }
    };
    Node *buildTree(std::vector<int>&fr);
    void dfs(Node *nd, std::vector<std::vector<bool>>&nw, std::vector<bool>&bits);

    public: 
    ~Huffman() override;
    void compress(const std::string& in, const std::string& out) override;
    void decompress(const std::string& in, const std::string& out) override;
};