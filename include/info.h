#pragma once
#include <iostream>
#include <string>

template <typename T>
class Info{
    public:
    static void actions(const std::string&action, const T& value) {
        std::cout << action << ' ' << value << '\n';
    }
};