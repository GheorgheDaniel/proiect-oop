#pragma once
#include "ICompressor.h"
#include "huffman.h"
#include "lzw.h"
#include "exceptions.h"

class CompressorDecider{
    public:
    static ICompressor* createCompressor(int type) {
        if(type == 1) return new Huffman();
        else if(type == 2) return new LZW();
        else throw CorruptArchiveE();
    }
};