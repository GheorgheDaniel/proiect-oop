#include "archivemanager.h"
#include "huffman.h"
#include "lzw.h"
#include "compressordecider.h"
#include "info.h"
#include <filesystem>
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include "binaryreader.h"
#include "binarywriter.h"
#include "encryptor.h"

const int MOD = 1e9 + 7;
const int B = 256;
size_t ArchiveManager::byteseconomisiti = 0;

void ArchiveManager::compress(const std::string& input, const std::string& password) {
    Info<std::string>::actions("COMPRESIA A INCEPUT", input);
    std::string input1 = input;
    /*
        de creat fisierul de iesire
        de testat care compresie e mai buna
        de aplicat compresia respectiva
    */

    int value = 0;
    for(int i = 0; i < (int)password.size(); i++) {
        value = ((1LL * value * B) % MOD + password[i]) % MOD;
    }

    
    std::string v1 = std::to_string(value);
    int value2 = 0;
    for(int i = 0; i < (int)v1.size(); i++) {
        value2 = ((1LL * value2 * B) % MOD + v1[i]) % MOD;
    }
    

    std::transform(input1.begin(), input1.end(), input1.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    std::string v; 
    if(input1.find(".") < input1.size())
    while(input1.back() != '.') {v.push_back(input1.back()); input1.pop_back();}
    std::reverse(v.begin(), v.end());
    if(mode == 1 || mode == 2) {
        AH.set_data(v, mode, value2);
        BinaryWriter fout(input1 + "bin");
        fout << AH;
        fout.close();
        // Huffman HF;
        // HF.compress(input, input1 + "bin");
        Info<int>::actions("SE RULEAZA ALGORITMUL: ", AH.get_algo_type());
        ICompressor* compresor = CompressorDecider::createCompressor(AH.get_algo_type());
        compresor->compress(input, input1 + "bin", value);
        delete compresor;
    }
    if(mode == 3) {
        AH.set_data(v, 1, value2);
        BinaryWriter foutH("huffman" + input1 + "bin");
        foutH << AH;
        foutH.close();
        Info<int>::actions("SE RULEAZA ALGORITMUL: ", AH.get_algo_type());
        ICompressor* compH = CompressorDecider::createCompressor(AH.get_algo_type());
        compH->compress(input, "huffman" + input1 + "bin", value);
        delete compH;

        AH.set_data(v, 2, value2);
        BinaryWriter foutL("LZW" + input1 + "bin");
        foutL << AH;
        foutL.close();
        Info<int>::actions("SE RULEAZA ALGORITMUL: ", AH.get_algo_type());
        ICompressor* compL = CompressorDecider::createCompressor(AH.get_algo_type());
        compL->compress(input, "LZW" + input1 + "bin", value);
        delete compL;

        size_t sizeh = std::filesystem::file_size("huffman" + input1 + "bin");
        size_t sizelzw = std::filesystem::file_size("LZW" + input1 + "bin");

        if(sizeh <= sizelzw) {
            std::filesystem::remove("LZW" + input1 + "bin");
            std::filesystem::rename("huffman" + input1 + "bin", input1 + "bin");
        }
        else {
            std::filesystem::remove("huffman" + input1 + "bin");
            std::filesystem::rename("LZW" + input1 + "bin", input1 + "bin");
        }
    }
    byteseconomisiti += std::filesystem::file_size(input) - std::filesystem::file_size(input1 + "bin");
}

void ArchiveManager::decompress(const std::string& input, const std::string& password) {
    Info<std::string>::actions("DECOMPRESIA A INCEPUT", input);
    BinaryReader fin(input);
    std::string input1 = input;
    if(input1.find(".") < input1.size())
    while(input1.back() != '.') {input1.pop_back();}

    fin >> AH;
    size_t alreadyread = fin.tellg();


    int value = 0;
    for(int i = 0; i < (int)password.size(); i++) {
        value = ((1LL * value * B) % MOD + password[i]) % MOD;
    }

    
    std::string v1 = std::to_string(value);
    int value2 = 0;
    for(int i = 0; i < (int)v1.size(); i++) {
        value2 = ((1LL * value2 * B) % MOD + v1[i]) % MOD;
    }
    if (value2 != AH.get_password()) {
        throw WrongPasswordE(); 
    }

    Info<int>::actions("SE RULEAZA ALGORITMUL: ", AH.get_algo_type());
    ICompressor* compresor = CompressorDecider::createCompressor(AH.get_algo_type());
    compresor->decompress(input, "recovered" + input1 + AH.get_extension(), alreadyread, value);
    Huffman* huff1 = dynamic_cast<Huffman*>(compresor); 

    if(huff1 != nullptr) {
        huff1->clearTree();
    }

    delete compresor;
    /*
        de verificat ce compresie e 
        de decompresat
    */

}