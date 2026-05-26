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
    archive_header() : algo_type(0), sz_ext(0) pass(0) {}
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

inline void archive_header::set_data(const std::string& ext, uint8_t at, int given_pass) {
    algo_type = at;
    sz_ext = ext.size();
    extension = ext;
    pass = given_pass;
}

inline BinaryReader &operator>>(BinaryReader &in, archive_header &c)
{
    in >> c.algo_type;
    in >> c.sz_ext;
    c.extension.resize(c.sz_ext);
    for (int i = 0; i < c.sz_ext; ++i) {
        in >> c.extension[i]; 
    }
    in >> c.pass;
    return in;
}

inline BinaryWriter &operator<<(BinaryWriter &out, const archive_header &c)
{
    out << c.algo_type; 
    out << c.sz_ext;
    for (char ch : c.extension) {
        out << ch;
    }
    out << c.pass;
    return out;
}
