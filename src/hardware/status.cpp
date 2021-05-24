#include "../constants/types.hpp"

struct Status {

    Bit* C;
    Bit* Z;
    Bit* I;
    Bit* D;
    Bit* B;
    Bit* V;
    Bit* N;

    Byte getByte() {
        return (*N << 7) | (*V << 6) | (*B << 4) | (*D << 3) | (*I << 2) | (*Z << 1) | *C;
    }

    void operator=(Byte S) {
        *N = (S >> 7) % 2;
        *V = (S >> 6) % 2;
        *B = (S >> 4) % 2;
        *D = (S >> 3) % 2;
        *I = (S >> 2) % 2;
        *Z = (S >> 1) % 2;
        *C = (S >> 0) % 2;
    }

    bool operator==(Byte S) {
        return S == getByte();
    }

    operator Byte() {
        return getByte();
    };

    Status(Bit *_C, Bit *_Z, Bit *_I, Bit *_D, Bit *_B, Bit *_V, Bit *_N) {
        C = _C;
        Z = _Z;
        I = _I;
        D = _D;
        B = _B;
        V = _V;
        N = _N;
    }

};