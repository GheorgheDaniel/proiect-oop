#pragma once
#include "archiveheader.h"

class ArchiveManager{
    private: 
    int mode;
    archive_header AH;
    static size_t byteseconomisiti;
    public:
    explicit ArchiveManager(int m = 1) : mode(m) {}
    static size_t getbytese() { return byteseconomisiti; }
    void compress(const std::string& in);
    void decompress(const std::string& in);
};