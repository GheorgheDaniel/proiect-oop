#include "archiveheader.h"

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
