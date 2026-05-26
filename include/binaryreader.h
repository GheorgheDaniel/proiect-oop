#pragma once
#include <fstream>
#include <bit>
#include <array>
#include <vector>
class BinaryReader{

    private:
        std::ifstream fin;
    public: 
        explicit BinaryReader(const std::string &input_file, size_t offset = 0) {
            fin.open(input_file, std::ios::binary);
            fin.seekg(offset);
        }
        ~BinaryReader() {
            fin.close();
        }

        template<typename T>
        BinaryReader& operator>>(T& val) {
            
            std::array<char, sizeof(T)> to_read;
            if(fin.read(to_read.data(), to_read.size())) 
            val = std::bit_cast<T>(to_read);
            return *this; 
        }

        explicit operator bool() const {
            return fin.good();
        }

        size_t tellg() { return fin.tellg();}


};