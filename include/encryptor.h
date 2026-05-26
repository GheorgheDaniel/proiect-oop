#include <random>


class Encrypt{
    public: 
    std::mt19937 rng;
    explicit Encrypt(int seed) : rng(seed) {};
    template<typename T>
    T encrypt(T val) {
        std::uniform_int_distribution<int>distrib(0, 255);
        val ^= distrib(rng);
        return val;
    }
};
