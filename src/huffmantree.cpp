#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "node.h"
#include "huffmantree.h"

HuffmanTree::~HuffmanTree() {
    freeTree(this->root); 
}

Node *HuffmanTree::copyNode(Node *tocopy) {
    if(tocopy == nullptr) return nullptr;
    Node *clone = new Node();
    clone->val = tocopy->val;
    clone->fr = tocopy->fr;
    clone->left = copyNode(tocopy->left);
    clone->right = copyNode(tocopy->right);
    return clone;
}

HuffmanTree::HuffmanTree(const HuffmanTree& other) {
    this->root = copyNode(other.root);
}

void HuffmanTree::clear() {
    freeTree(this->root); 
    this->root = nullptr; 
}

HuffmanTree& HuffmanTree::operator=(const HuffmanTree& other) {
    if (this != &other) {
        freeTree(this->root);
        this->root = copyNode(other.root);
    }
    return *this; 
}

void HuffmanTree::buildTree(const std::vector<int>&fr) {
        std::priority_queue<Node *, std::vector<Node *>, 
            std::function<bool(const Node*, const Node*)>> pq(
        [](const Node* n1, const Node* n2) { return n1->fr > n2->fr; });
        for(int i = 0; i < 256; i++) {
            if(fr[i])
            {
                Node *nd = new Node();
                nd->val = i;
                nd->fr = fr[i];
                pq.push(nd);
            }
        }
        Node *node1;
        Node *node2;
        while(pq.size() > 1) {
            node1 = pq.top();
            pq.pop();
            node2 = pq.top();
            pq.pop();
            Node *node3 = new Node(*node1 + *node2);
            node3->left = node1;
            node3->right = node2;
            pq.push(node3);

        }
        if(!pq.empty()) {this->root = pq.top();}
    }   

void HuffmanTree::dfs(Node *nd, std::vector<std::vector<bool>>&nw, std::vector<bool>&bits) {
        if(nd->left != nullptr) {
            bits.push_back(0);
            dfs(nd->left, nw, bits);
            bits.pop_back();
            bits.push_back(1);
            dfs(nd->right, nw, bits);
            bits.pop_back();
        }
        else {  
            nw[nd->val] = bits;
        }
    }

void HuffmanTree::freeTree(Node *nd) {
    if(nd == nullptr) return ;
    freeTree(nd->left);
    freeTree(nd->right);
    delete nd;
}

void HuffmanTree::generateCodes(std::vector<std::vector<bool>>& nw) {
    if (root != nullptr) {
        std::vector<bool> bits;
        dfs(root, nw, bits);
    }
}

