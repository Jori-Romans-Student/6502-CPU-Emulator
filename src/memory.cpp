#include "constants.hpp"

struct Mem {
    static constexpr u32 MAX_MEM = 256 * 256;
    Byte Data[MAX_MEM]; 

    void Initialize() {
        for ( u32 i = 0; i < MAX_MEM; i++ ) {
            Data[i] = 0;
        }
    }

    Byte operator[](u32 address) const {
        return Data[address];
    }

    Byte& operator[](u32 address) {
        return Data[address];
    }

    Mem() {
        Initialize();
    };
};