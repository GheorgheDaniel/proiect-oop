#pragma once
#include <iostream>
#include <cstring>
#include <cstdint>
class archive_header{
    private:
    uint8_t algo_type;
    uint8_t sz_ext;
    std::string extension;  

    public:
    public:
    archive_header() : algo_type(0), sz_ext(0) {}
    uint8_t get_algo_type() const {return algo_type;}
    std::string get_extension() const {return extension; }
    void set_data(const std::string& ext, uint8_t at);
    friend std::istream &operator>>(std::istream &in, archive_header &c);
    friend std::ostream &operator<<(std::ostream &out, const archive_header &c);
};

/*

    Formatul header-ului e :
    -> tipul algoritmului
    -> dimensiunea extensiei
    -> extensia

*/

inline void archive_header::set_data(const std::string& ext, uint8_t at) {
    algo_type = at;
    sz_ext = ext.size();
    extension = ext;
}

inline std::istream &operator>>(std::istream &in, archive_header &c)
{
    c.algo_type = in.get();
    c.sz_ext = in.get();
    c.extension.resize(c.sz_ext);
    in.read(&c.extension[0], c.sz_ext);
    return in;
}

inline std::ostream &operator<<(std::ostream &out, const archive_header &c)
{
    out.put(c.algo_type);
    out.put(c.sz_ext);
    out.write(c.extension.c_str(), c.sz_ext);
    return out;
}
