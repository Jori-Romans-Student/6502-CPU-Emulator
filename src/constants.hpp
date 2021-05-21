// ========== Types ==========

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;
using Signed = signed char;

using Bit = bool;

struct Status {

    Bit* C;
    Bit* Z;
    Bit* I;
    Bit* D;
    Bit* B;
    Bit* V;
    Bit* N;

    void operator=(Byte S) {
        *N = (S >> 7) % 2;
        *V = (S >> 6) % 2;
        *B = (S >> 4) % 2;
        *D = (S >> 3) % 2;
        *I = (S >> 2) % 2;
        *Z = (S >> 1) % 2;
        *C = (S >> 0) % 2;
    }

    operator Byte() {
        return (*N << 7) | (*V << 6) | (*B << 4) | (*D << 3) | (*I << 2) | (*Z << 1) | *C;
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

bool isPositive(Byte value) {
    return (value & 0b10000000) == 0;
}

bool isNegative(Byte value) {
    return (value & 0b10000000) != 0;
}

bool isZero(Byte value) {
    return value == 0;
}

bool isOverflow(Byte value) {
    return (value & 0b01000000) != 0;
}

bool isAddedOverflow(Byte valueOne, Byte valueTwo) {
    return (~(valueOne ^ valueTwo) & (valueOne ^ (valueOne + valueTwo)) & 0x80) > 0;
}

bool isSubtractedOverflow(Byte valueOne, Byte valueTwo) {
    return ((valueOne ^ valueTwo) & (valueOne ^ (valueOne - valueTwo)) & 0x80) > 0;
}

bool isOdd(Byte value) {
    return (value & 0b00000001) != 0;
}

bool isClear(Bit value) {
    return !value;
}

bool isSet(Bit value) {
    return value;
}

// Codes

#define AB 0x00
#define ABX 0x01
#define ABY 0x02
#define AC 0x03
#define ID 0x04
#define IDX 0x05
#define IDY 0x06
#define IMM 0x07
#define REL 0x08
#define ZP 0x09
#define ZPX 0x0A
#define ZPY 0x0B

// Instructions

#define ADC 0x00
#define AND 0x01
#define ASL 0x02
#define BCC 0x03
#define BCS 0x04
#define BEQ 0x05
#define BIT 0x06
#define BMI 0x07
#define BNE 0x08
#define BPL 0x09
#define BRK 0x0A
#define BVC 0x0B
#define BVS 0x0C
#define CLC 0x0D
#define CLD 0x0E
#define CLI 0x0F
#define CLV 0x10
#define CMP 0x11
#define CPX 0x12
#define CPY 0x13
#define DEC 0x14
#define DEX 0x15
#define DEY 0x16
#define EOR 0x17
#define INC 0x18
#define INX 0x19
#define INY 0x1A
#define JMP 0x1B
#define JSR 0x1C
#define LDA 0x1D
#define LDX 0x1E
#define LDY 0x1F
#define LSR 0x20
#define NOP 0x21
#define ORA 0x22
#define PHA 0x23
#define PHP 0x24
#define PLA 0x25
#define PLP 0x26
#define ROL 0x27
#define ROR 0x28
#define RTI 0x29
#define RTS 0x2A
#define SBC 0x2B
#define SEC 0x2C
#define SED 0x2D
#define SEI 0x2E
#define STA 0x2F
#define STX 0x30
#define STY 0x31
#define TAX 0x32
#define TAY 0x33
#define TSX 0x34
#define TXA 0x35
#define TXS 0x36
#define TYA 0x37