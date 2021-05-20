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

        Word address;

        switch (mode) {
            case AB: return Fetch() << 8 | Fetch(); break;
            case ABX: return (Fetch() << 8 | Fetch()) + X; break;
            case ABY: return (Fetch() << 8 | Fetch()) + Y; break;
            case IMM: address = PC; PC++; return address; break;
            case ID: address = Fetch() << 8 | Fetch(); return Read(address) << 8 | Read(address + 1); break;
            case IDX: address = Fetch(); return Read(address + X) << 8 | Read(address + X + 1); break;
            case IDY: address = Fetch(); return (Read(address) << 8 | Read(address + 1)) + Y; break;
            case REL: address = PC; PC++; return address; break;
            case ZP: return Fetch(); break;
            case ZPX: return Fetch() + X; break;
            case ZPY: return Fetch() + Y; break;
        }

        return 0xFF;
    };

    Byte Instruct(Byte code) {
        switch ((code & 0xE0) >> 3 | (code & 0x03)) {
            case 0x00:
                if (code == 0x00) return BRK;
                else if (code == 0x08) return PHP;
                else if (code == 0x10) return BPL;
                else if (code == 0x18) return CLC;
                break;
            case 0x01: return ORA; break;
            case 0x02: return ASL; break;
            case 0x04:
                if ((code & 0x07) == 0x04) return BIT;
                else if (code == 0x20) return JSR;
                else if (code == 0x28) return PLP;
                else if (code == 0x30) return BMI;
                else if (code == 0x38) return SEC;
                break;
            case 0x05: return AND; break;
            case 0x06: return ROL; break;
            case 0x08:
                if (code == 0x40) return RTI;
                else if (code == 0x48) return PHA;
                else if (code == 0x4C) return JMP;
                else if (code == 0x50) return BVC;
                else if (code == 0x58) return CLI;
                break;
            case 0x09: return EOR;
            case 0x0A: return LSR;
            case 0x0C:
                if (code == 0x60) return RTS;
                else if (code == 0x68) return PLA;
                else if (code == 0x6C) return JMP;
                else if (code == 0x70) return BVS;
                else if (code == 0x78) return SEI;
                break;
            case 0x0D: return ADC; break;
            case 0x0E: return ROR; break;
            case 0x10:
                if ((code & 0x07) == 0x04) return STY;
                else if (code == 0x88) return DEY;
                else if (code == 0x90) return BCC;
                else if (code == 0x98) return TYA;
                break;
            case 0x11: return STA; break;
            case 0x12:
                if (code == 0x8A) return TXA;
                else if (code == 0x9A) return TXS; 
                else return STX; 
                break;
            case 0x14:
                if ((code & 0x07) == 0x04 || code == 0xA0) return LDY;
                else if (code == 0xA8) return TAY;
                else if (code == 0xB0) return BCS;
                else if (code == 0xB8) return CLV;
                break;
            case 0x15: return LDA; break;
            case 0x16: 
                if (code == 0xAA) return TAX; 
                else if (code == 0xBA) return TSX;
                else return LDX; 
                break;
            case 0x18:
                if ((code & 0x07) == 0x04 || code == 0xC0) return CPY;
                else if (code == 0xC8) return INY;
                else if (code == 0xD0) return BNE;
                else if (code == 0xD8) return CLD;
                break;
            case 0x19: return CMP; break;
            case 0x1A:
                if (code == 0xCA) return DEX;
                else return DEC;
                break;
            case 0x1C:
                if ((code & 0x07) == 0x04 || code == 0xE0) return CPX;
                else if (code == 0xE8) return INX;
                else if (code == 0xF0) return BEQ;
                else if (code == 0xF8) return SED;
                break;
            case 0x1D: return SBC; break;
            case 0x1E:
                if (code == 0xEA) return NOP;
                else return INC;
                break;
        }
        return 0xFF;
    };

    void Execute(Byte mode, Word address) {
        
        Byte store; // Used if any storage is required between lines

        switch (mode) {
            case ADC: store = Read(address) + C; V = (~(A ^ store) & (A ^ (A + store)) & 0x80) > 0; C = V; A = (Byte) (A + store); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case AND: A = A & Read(address); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case ASL: store = Read(address); C = (store & 0b10000000) > 0; store = store << 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case BCC: store = Read(address); if (C == 0) PC += (signed char) store; break;
            case BCS: store = Read(address); if (C == 1) PC += (signed char) store; break;
            case BEQ: store = Read(address); if (Z == 1) PC += (signed char) store; break;
            case BIT: store = Read(address); Z = ((A & store) == 0); N = (store & 0b10000000) > 0; V = (store & 0b01000000) > 0; break;
            case BMI: store = Read(address); if (N == 1) PC += (signed char) store; break;
            case BNE: store = Read(address); if (Z == 0) PC += (signed char) store; break;
            case BPL: store = Read(address); if (N == 0) PC += (signed char) store; break;
            case BRK: store = (N << 7) | (V << 6) | (B << 4) | (D << 3) | (I << 2) | (Z << 1) | C; Push((Byte) (PC >> 8)); Push((Byte) PC); Push(store); PC = (Read(0xFFFE) << 8 | Read(0xFFFF)); B = 1; break;
            case BVC: store = Read(address); if (V == 0) PC += (signed char) store; break;
            case BVS: store = Read(address); if (V == 1) PC += (signed char) store; break;
            case CLC: C = 0; break;
            case CLD: D = 0; break;
            case CLI: I = 0; break;
            case CLV: V = 0; break;
            case CMP: store = Read(address); Z = (A == store); N = ((A - store) & 0b10000000) > 0; C = (A >= store); break;
            case CPX: store = Read(address); Z = (X == store); N = ((X - store) & 0b10000000) > 0; C = (X >= store); break;
            case CPY: store = Read(address); Z = (Y == store); N = ((Y - store) & 0b10000000) > 0; C = (Y >= store); break;
            case DEC: store = Read(address) - 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case DEX: X -= 0x01; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case DEY: Y -= 0x01; Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case EOR: A = (A ^ Read(address)); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case INC: store = Read(address) + 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case INX: X += 0x01; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case INY: Y += 0x01; Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case JMP: PC = address; break;
            case JSR: Push((Byte) ((PC - 1) >> 8)); Push((Byte) (PC - 1)); PC = address; break;
            case LDA: A = Read(address); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case LDX: X = Read(address); Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case LDY: Y = Read(address); Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case LSR: store = Read(address); C = (store & 0b00000001) > 0; store = store >> 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case ORA: A = (A | Read(address)); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case PHA: Push(A); break;
            case PHP: store = (N << 7) | (V << 6) | (B << 4) | (D << 3) | (I << 2) | (Z << 1) | C; Push(store); break;
            case PLA: A = Pull(); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case PLP: store = Pull(); N = (store >> 7) % 2; V = (store >> 6) % 2; B = (store >> 4) % 2; D = (store >> 3) % 2; I = (store >> 2) % 2; Z = (store >> 1) % 2; C = store % 2; break;
            case ROL: store = Read(address); N = (store & 0b10000000) > 0; store = (store << 1) + C; Write(address, store); Z = (store == 0); C = N; N = (store & 0b10000000) > 0; break;
            case ROR: store = Read(address); N = (store & 0b00000001) > 0; store = (store >> 1) | (C << 7); Write(address, store); Z = (store == 0); C = N; N = (store & 0b10000000) > 0; break;
            case RTI: store = Pull(); N = (store >> 7) % 2; V = (store >> 6) % 2; B = (store >> 4) % 2; D = (store >> 3) % 2; I = (store >> 2) % 2; Z = (store >> 1) % 2; C = store % 2; PC = (Word) Pull(); PC = (Word) (Pull() << 8 | PC); break;
            case RTS: PC = (Word) Pull(); PC = (Word) (Pull() << 8 | PC); break;
            case SBC: store = Read(address) + (C ^ 0x01); V = ((A ^ store) & (A ^ (A - store)) & 0x80) > 0; C = ~V; A = (Byte) (A - store); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case SEC: C = 1; break;
            case SED: D = 1; break;
            case SEI: I = 1; break;
            case STA: Write(address, A); break;
            case STX: Write(address, X); break;
            case STY: Write(address, Y); break;
            case TAX: X = A; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case TAY: Y = A; Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case TSX: X = S; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case TXA: A = X; Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case TXS: S = X; break;
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