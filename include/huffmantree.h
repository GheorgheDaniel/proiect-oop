#pragma once
#include <vector>
#include "node.h"


class HuffmanTree{
    private:
    Node* root;
    Node* copyNode(Node* original);

    public:
    HuffmanTree(const HuffmanTree& other);
    HuffmanTree& operator=(const HuffmanTree& other);
    Node* getRoot() const { return root; }
    HuffmanTree(): root(nullptr) {};
    ~HuffmanTree();
    void buildTree(std::vector<int>&fr);
    void generateCodes(std::vector<std::vector<bool>>& nw);
    void clear();
    private:
    void dfs(Node *nd, std::vector<std::vector<bool>>&nw, std::vector<bool>&bits);
    void freeTree(Node *nd);
};
