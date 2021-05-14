#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "memory.cpp"

// Codes

#define AB 0x0
#define ABX 0x1
#define ABY 0x2
#define AC 0x3
#define IMM 0x4
#define ID 0x5
#define IDX 0x6
#define IDY 0x7
#define REL 0x8
#define ZP 0x9
#define ZPX 0xA
#define ZPY 0xB


struct CPU{
    
    // Progarm Counter and Stack Pointer

    Word PC;
    Byte SP;
    Mem* mem;

    // Registers

    Byte A, X, Y;

    // Process Status Flags

    Byte C : 1;
    Byte Z : 1;
    Byte I : 1;
    Byte D : 1;
    Byte B : 1;
    Byte V : 1;
    Byte N : 1;

    Byte Read(Word address) {
        return (*mem)[address];
    };

    void Write(Word address, Byte value) {
        (*mem)[address] = value;
    }
    
    Byte Fetch() {
        
        // Get value and increment PC

        Byte value = (*mem)[PC];
        PC++;

        // Return value

        return value;
    };

    // Get ADRM bits bbb from OP code aaabbbcc, then filter based on low nibble

    Byte Decode(Byte code) {

        switch ((code & 0x1C) >> 2) {
            case 0x0: 
                if (code == 0x20) return AB;
                else if (code == 0x00 || code == 0x40 || code == 0x60) return AC;
                else if ((code & 0x0F) == 0x1) return IDX;
                else if (code > 0x80) return IMM;
                break;
            case 0x1:
                return ZP;
                break;
            case 0x2:
                if ((code & 0x0F) == 0x8 || (code & 0x0F) == 0xA) return AC;
                else if ((code & 0x0F) == 0x09) return IMM;
                break;
            case 0x3: 
                if (code == 0x6C) return ID; 
                else return AB;
                break;
            case 0x4:
                if ((code & 0x0F) == 0x1) return IDY;
                else if ((code & 0x0F) == 0x0) return REL;
                break;
            case 0x5:
                if (code == 0x96 || code == 0xB6) return ZPY;
                else return ZPX;
                break;
            case 0x6:
                if ((code & 0x0F) == 0x9) return ABY;
                else if ((code & 0x0F) == 0x8 || (code & 0x0F) == 0xA) return AC;
                break;
            case 0x7:
                if (code == 0xBE) return ABY;
                else return ABX; 
                break;
            default: return 0xFF;
        }
    }

    Word Address(Byte mode) {
        switch (mode) {
            case AB: return Fetch() << 8 | Fetch();
            case ABX: return (Fetch() << 8 | Fetch()) + X;
            case ABY: return (Fetch() << 8 | Fetch()) + Y; 
            case IMM: return PC;
            case IDX: Byte address = Fetch(); return Read(address + X) << 8 | Read(address + X + 1);
            case IDY: Byte address = Fetch(); return (Read(address) << 8 | Read(address + 1)) + Y;
            case ZP: return Fetch();
            case ZPX: return Fetch() + X;
            case ZPY: return Fetch() + Y;
        }
    }

    CPU(Mem *_mem ) {
        mem = _mem;
    };
};