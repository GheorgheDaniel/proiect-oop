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
#include "binaryreader.h"
#include "binarywriter.h"

LZW::~LZW() {

}
    
    /*

        Functia compress va functiona in felul urmator: 
            -> todo
    
    */
void LZW::compress(const std::string& input, const std::string& output) {
    BinaryReader fin(input);
    BinaryWriter fout(output, 1);  

    std::vector<char>data = fin.readall();
    std::unordered_map<std::string, uint16_t>dict;
    std::string pfx;
    uint16_t val = 256;
    for(int i = 0; i < 256; i++) {
        std::string s;
        s += i;
        dict[s] = (uint16_t)i;
    }   

    for(auto chr : data){
        pfx += chr;
        if(dict.count(pfx)) continue;
        else {
            pfx.pop_back();
            fout << dict[pfx];
            if(val < (1 << 16) - 1) {
                dict[pfx + chr] = val;
                val++;
            }
            pfx = chr;
        }
    }
    if(!pfx.empty()) {
        fout << dict[pfx];
    }

}

void LZW::decompress(const std::string& input, const std::string& output, size_t alreadyread) {
    BinaryReader fin(input, alreadyread);
    BinaryWriter fout(output);

    std::vector<std::string> dict;
    for(int i = 0; i < 256; i++) {
        std::string i1;
        i1.push_back(i);
        dict.push_back(i1);
    }

    uint16_t ceva_cod;
    std::string antechr;
    uint16_t ante_cod;
    fin >> ante_cod;
    antechr += dict[ante_cod];
    
    for (char c : antechr) {
        fout << c;
    }

    std::string actualul;
    while(fin >> ceva_cod) {
        if(ceva_cod < dict.size()) {actualul = dict[ceva_cod];}
        else {
            if(ceva_cod == dict.size()) {actualul = antechr + antechr[0]; }
            else {
                //tre sa pun eroare
                throw CorruptArchiveE();
            }
        }
        for (char c : actualul) {
            fout << c;
        }
        if(dict.size() < (1 << 16) - 1) {dict.push_back(antechr + actualul[0]); }
        antechr = actualul;
    }

}

