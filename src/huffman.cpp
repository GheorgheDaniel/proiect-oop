#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "huffman.h"
#include "exceptions.h"
#include "binaryreader.h"
#include "binarywriter.h"
#include "encryptor.h"
Huffman::~Huffman() {

}


    /*

        Functia compress va functiona in felul urmator: 
            -> construiesc copacul
            -> pun frecventele in fisierul de iesire
            -> pun sirul compresat in fisierul de iesire
    
    */
void Huffman::compress(const std::string& input, const std::string& output, const int password) {
        BinaryReader fin(input);
        BinaryWriter fout(output, 1);
        std::vector<char> data;
        Encrypt e(password);

        char chr;
        while(fin >> chr) {
            data.push_back(chr);
        }
        
        std::vector<int>fr(256);
        for(auto i : data) fr[(uint8_t)i]++;
        HT.buildTree(fr);
        std::vector<std::vector<bool>> compressed(256); 
        HT.generateCodes(compressed);


        /*
        
            Mai e de citit:
            Lungimea fisierului initial
            vectorul de frecvente
            sirul compresat

        */

        //de revazut bucata asta daca e ok
        size_t original_size = data.size();
        fout << e.encrypt(original_size);
        for(auto fq : fr) {
            fout << e.encrypt(fq);
        }

        uint8_t buffer = 0, bit = 0;

        for(auto i : data) {
            for(auto bt : compressed[(uint8_t)i]) {
                buffer |= (bt << (7 - bit));
                bit++;
                if(bit == 8) {
                    fout << e.encrypt(buffer);
                    bit = 0; buffer = 0;
                }


            }
        }   
        if(bit != 0) {
            fout << e.encrypt(buffer);
        }

}

void Huffman::decompress(const std::string& input, const std::string& output, size_t offset, const int password) {
    BinaryReader fin(input, offset);
    Encrypt e(password);

    size_t len;
    fin >> len;
    len = e.encrypt(len);
    std::vector<int>fr(256);
    for (int i = 0; i < 256; ++i) {
        fin >> fr[i];
        fr[i] = e.encrypt(fr[i]);
    }

    std::vector<char> arhiva;
    char chr;
    while(fin >> chr) {arhiva.push_back(e.encrypt(chr));}

    HT.buildTree(fr);
    Node *nd = HT.getRoot();
    if (nd == nullptr) return;
    Node *ndaux = nd;

    size_t poz = 0;
    BinaryWriter fout(output);

    // std::vector<char>decomp;
    for (auto i : arhiva)
    {   
        for(uint8_t idx = 0; idx < 8; idx++) {
            uint8_t bit = ((((uint8_t)i) >> (7 - idx)) & 1);
            if(bit == 1) {ndaux = ndaux->right;}
            else {ndaux = ndaux->left;}    
            
            if (ndaux->left == nullptr) {
                fout << (char)ndaux->val;     
                // decomp.push_back((char)ndaux->val);           
                ndaux = nd;
                poz++;
                if(poz == len) {
                    return ;
                }
            }
        }
    }
}

void Huffman::clearTree() {
    HT.clear();
    std::cout << "Arborele Huffman a fost golit.\n";
}