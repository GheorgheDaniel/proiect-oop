#include <bits/stdc++.h>
#include "../include/huffman.h"

Huffman::~Huffman() {

}

Huffman::Node *Huffman::buildTree(std::vector<int>&fr) {
        std::priority_queue<pii>pq;
        for(int i = 0; i < 256; i++) {
            if(fr[i])
            {
                Node *nd = new Node;
                nd->val = i;
                pq.push({fr[i], (uint8_t)i, nd});
            }
        }
        while(pq.size() > 1) {
            auto [fr1, val1, nod1] = pq.top();
            pq.pop();
            auto [fr2, val2, nod2] = pq.top();
            pq.pop();
            Node *nd = new Node;
            nd->left = nod1; nd->right = nod2;
            pq.push({fr1 + fr2, 0, nd});

        }

        return pq.top().nd;
    }   

void Huffman::dfs(Huffman::Node *nd, std::vector<std::vector<bool>>&nw, std::vector<bool>&bits) {
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
    /*

        Functia compress va functiona in felul urmator: 
            -> construiesc copacul
            -> pun frecventele in fisierul de iesire
            -> pun sirul compresat in fisierul de iesire
    
    */
void Huffman::compress(const std::string& input, const std::string& output) {
        std::ifstream fin(input, std::ios::binary);
        
        if (!fin.is_open()) {
            throw std::runtime_error("Lipseste fisierul de intrare");
        }
        std::vector<uint8_t> data(
            (std::istreambuf_iterator<char>(fin)), 
            std::istreambuf_iterator<char>()
        );
        fin.close();

        std::vector<int>fr(256);
        for(auto i : data) fr[i]++;
        Huffman::Node *nd = Huffman::buildTree(fr);
        std::vector<std::vector<bool>>compressed(256); 
        std::vector<bool>bits;
        Huffman::dfs(nd, compressed, bits);

        std::ofstream fout(output, std::ios::binary);
        if(!fout.is_open()) {
            throw std::runtime_error("Lipseste fisier iesire");
        }   

        /*
        
            Formatul fisierului de iesire va fi:
            Lungimea fisierului initial
            vectorul de frecvente
            sirul compresat

        */

        //de revazut bucata asta daca e ok
        size_t original_size = data.size();
        fout.write(reinterpret_cast<const char*>(&original_size), sizeof(size_t));
        fout.write(reinterpret_cast<const char*>(fr.data()), 256 * sizeof(int));

        uint8_t buffer = 0, bit = 0;

        for(auto i : data) {
            for(auto bt : compressed[i]) {
                buffer |= (bt << (7 - bit));
                bit++;
                if(bit == 8) {
                    fout.put((char)buffer);
                    bit = 0; buffer = 0;
                }


            }
        }   
        if(bit != 0) {
            fout.put((char)buffer);
        }
        fout.close();

    }





void Huffman::decompress(const std::string& input, const std::string& output) {
    std::ifstream fin(input, std::ios::binary);
        
    if (!fin.is_open()) {
        throw std::runtime_error("Lipseste fisierul de intrare");
    }
    size_t len;
    fin.read(reinterpret_cast<char*>(&len), sizeof(size_t));

    std::vector<int>fr(256);
    fin.read(reinterpret_cast<char*>(fr.data()), 256 * sizeof(int));

    std::vector<uint8_t> arhiva(
        (std::istreambuf_iterator<char>(fin)), 
        std::istreambuf_iterator<char>()
    );
    fin.close();

    Huffman::Node *nd = buildTree(fr);
    Huffman::Node *ndaux = nd;

    size_t poz = 0;
    std::ofstream fout(output, std::ios::binary);
    if(!fout.is_open()) {
        throw std::runtime_error("Lipseste fisier iesire");
    }   

    for (auto i : arhiva)
    {   
        for(uint8_t idx = 0; idx < 8; idx++) {
            uint8_t bit = ((i >> (7 - idx)) & 1);
            if(bit == 1) {ndaux = ndaux->right;}
            else {ndaux = ndaux->left;}    
            
            if (ndaux->left == nullptr) {
                fout.put((char)ndaux->val);                
                ndaux = nd;
                poz++;
                if(poz == len) {
                    fout.close();
                    return ;
                }
            }
        }
    }
    fout.close();
}


