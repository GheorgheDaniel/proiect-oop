#pragma once
#include <fstream>
#include <bit>
#include <array>
#include <vector>

class BinaryWriter{

    private:
        std::ofstream fout;
    public: 
        BinaryWriter(const std::string &output_file, bool append = false) {
            if (append) {
                fout.open(output_file, std::ios::binary | std::ios::app);
            } else {
                fout.open(output_file, std::ios::binary);
            }
        }
        ~BinaryWriter() {
            fout.close();
        }

        template<typename T>
        BinaryWriter& operator<<(const T& val) {
            
            auto biti = std::bit_cast<std::array<char, sizeof(T)>>(val);
            fout.write(biti.data(), biti.size());
            return *this; 
        }
        void writeall(const std::vector<char>& data) {
            fout.write(data.data(), data.size());
        }
        void close() {
            if (fout.is_open()) {
                fout.close();
            }
        }
};