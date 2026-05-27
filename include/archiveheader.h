#pragma once
#include <iostream>
#include <cstring>
#include <cstdint>
#include "binaryreader.h"
#include "binarywriter.h"

class archive_header{
    private:
    uint8_t algo_type;
    uint8_t sz_ext;
    std::string extension;  
    int pass;

    public:
    archive_header() : algo_type(0), sz_ext(0), pass(0) {}
    uint8_t get_algo_type() const {return algo_type;}
    int get_password() const {return pass; }
    const std::string& get_extension() const {return extension; }
    void set_data(const std::string& ext, uint8_t at, int pass);
    friend BinaryReader& operator>>(BinaryReader &in, archive_header &c);
    friend BinaryWriter& operator<<(BinaryWriter &out, const archive_header &c);
};

/*

    Formatul header-ului e :
    -> tipul algoritmului
    -> dimensiunea extensiei
    -> extensia

*/
