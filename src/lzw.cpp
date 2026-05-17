#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <functional>
#include "lzw.h"
#include "exceptions.h"


LZW::~LZW() {

}
    
    /*

        Functia compress va functiona in felul urmator: 
            -> todo
    
    */
void LZW::compress(const std::string& input, const std::string& output) {
    std::ifstream fin(input, std::ios::binary);
    std::ofstream fout(output, std::ios::binary | std::ios::app);  
    if (!fin.is_open()) {
        throw FileMissingE(input);
    }

    std::unordered_map<std::string, uint16_t>dict;
    std::string pfx;
    uint16_t val = 256;
    for(int i = 0; i < 256; i++) {
        std::string s;
        s += i;
        dict[s] = (uint16_t)i;
    }   
    char chr;

    while(fin.get(chr)) {
        pfx += chr;
        if(dict.count(pfx)) continue;
        else {
            pfx.pop_back();
            fout.write(reinterpret_cast<char*>(&dict[pfx]), sizeof(dict[pfx]));
            if(val < (1 << 16) - 1) {
                dict[pfx + chr] = val;
                val++;
            }
            pfx = chr;
        }
    }
    if(!pfx.empty()) {
        fout.write(reinterpret_cast<char*>(&dict[pfx]), sizeof(dict[pfx]));
    }

}

void LZW::decompress(const std::string& input, const std::string& output, size_t alreadyread) {
    std::vector<std::string> dict;
    std::ifstream fin(input, std::ios::binary);
    fin.seekg(alreadyread);
    for(int i = 0; i < 256; i++) {
        std::string i1;
        i1.push_back(i);
        dict.push_back(i1);
    }

    uint16_t ceva_cod;
    std::string antechr;
    uint16_t ante_cod;
    fin.read(reinterpret_cast<char*>(&ante_cod), sizeof(ante_cod));
    antechr += dict[ante_cod];
    
    std::ofstream fout(output, std::ios::binary);
    fout.write(antechr.c_str(), antechr.size());

    std::string actualul;
    while(fin.read(reinterpret_cast<char*>(&ceva_cod), sizeof(ceva_cod))) {
        if(ceva_cod < dict.size()) {actualul = dict[ceva_cod];}
        else {
            if(ceva_cod == dict.size()) {actualul = antechr + antechr[0]; }
            else {
                //tre sa pun eroare
                throw CorruptArchiveE();
            }
        }
        fout.write(actualul.c_str(), actualul.size());
        if(dict.size() < (1 << 16) - 1) {dict.push_back(antechr + actualul[0]); }
        antechr = actualul;
    }
    fout.close();
    fin.close();
}

