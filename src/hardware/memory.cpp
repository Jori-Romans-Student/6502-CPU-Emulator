#include "../constants/types.hpp"

struct Mem {
    static constexpr int MAX_MEM = 256 * 256;
    Byte Data[MAX_MEM]; 

    void Initialize() {
        for ( int i = 0; i < MAX_MEM; i++ ) {
            Data[i] = 0;
        }
    }

    Byte operator[](Word address) const {
        return Data[address];
    }

    Byte& operator[](Word address) {
        return Data[address];
    }

    Mem() {
        Initialize();
    };
};