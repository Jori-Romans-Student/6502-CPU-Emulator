#include <stdio.h>
#include <stdlib.h>
#include <map>
#include "memory.cpp"

struct CPU {
    
    // Progarm Counter and Stack Pointer

    Word PC;
    Byte S;
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

    Byte Pull() {
        S--;
        return Read((Word) (0x0100 | S));
    }

    void Push(Byte value) {
        Write((Word) (0x0100 | S), value);
        S++;
    }
    
    // Get value and increment PC

    Byte Fetch() {

        Byte value = (*mem)[PC];
        PC++;

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
        }
        return 0xFF;
    };

    Word Address(Byte mode) {

        Byte address;

        switch (mode) {
            case AB: return Fetch() << 8 | Fetch(); break;
            case ABX: return (Fetch() << 8 | Fetch()) + X; break;
            case ABY: return (Fetch() << 8 | Fetch()) + Y; break;
            case IMM: return PC; break;
            case IDX: address = Fetch(); return Read(address + X) << 8 | Read(address + X + 1); break;
            case IDY: address = Fetch(); return (Read(address) << 8 | Read(address + 1)) + Y; break;
            case ZP: return Fetch(); break;
            case ZPX: return Fetch() + X; break;
            case ZPY: return Fetch() + Y; break;
        }

        return 0xFF;
    };

    Byte Instruct(Byte code) {
        switch ((code & 0xE0) >> 3 | (code & 0x03)) {
            case 0x10:
                if (code == 0x98) return TYA;
                else if ((code & 0x0F) != 0x08) return STY;
                break;
            case 0x11: return STA; break;
            case 0x12:
                if (code == 0x8A) return TXA; 
                else return STX; 
                break;
            case 0x14:
                if ((code & 0x0F) == 0x04 || (code & 0x0F) == 0x0C || code == 0xA0) return LDY;
                else if (code == 0xA8) return TAY;
                break;
            case 0x15: return LDA; break;
            case 0x16: 
                if (code == 0xAA) return TAX; 
                else if (code == 0xBA) return TSX;
                else return LDX; 
                break;
        }
        return 0xFF;
    };

    void Execute(Byte mode, Word address) {
        switch (mode) {
            case LDA: A = Read(address); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case LDX: X = Read(address); Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case LDY: Y = Read(address); Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case STA: Write(address, A); break;
            case STX: Write(address, X); break;
            case STY: Write(address, Y); break;
            case TAX: X = A; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case TAY: Y = A; Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case TSX: Push(X); Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case TXA: A = X; Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case TYA: A = Y; Z = (A == 0); N = (A & 0b10000000) > 0; break;
        }
    }

    void Run() {
        Byte OP = Fetch();
        Byte ADRM = Decode(OP);
        Word ADR = Address(ADRM);
        Byte INS = Instruct(OP);
        Execute(INS, ADR);
    }

    CPU(Mem *_mem ) {
        mem = _mem;
        S = 0x00;
    };
};