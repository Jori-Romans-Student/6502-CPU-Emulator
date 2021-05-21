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

    Bit C = 0;
    Bit Z = 0;
    Bit I = 0;
    Bit D = 0;
    Bit B = 0;
    Bit V = 0;
    Bit N = 0;

    // Processor Byte

    Status P = Status(&C, &Z, &I, &D, &B, &V, &N);

    template <typename T>
    T Read(Word address) {

        int bytes = (int) (sizeof(T) / sizeof(Byte));

        Byte value;
        T data = 0;

        for (int i = 1; i <= bytes; i++) {
            value = (*mem)[address + i - 1];
            data |= value << ((bytes - i) * 8);
        }

        return data;
    };

    void Write(Word address, Byte value) {
        (*mem)[address] = value;
    }

    Byte Pull() {
        S--;
        return Read<Byte>((Word) (0x0100 | S));
    }

    void Push(Byte value) {
        Write((Word) (0x0100 | S), value);
        S++;
    }
    
    // Get value and increment PC

    template <typename T>
    T Fetch() {

        int bytes = (int) (sizeof(T) / sizeof(Byte));
        
        Byte value;
        T data = 0;

        for (int i = 1; i <= bytes; i++) {
            value = (*mem)[PC];
            data |= value << ((bytes - i) * 8);
            PC++;
        }

        return data;

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
            case AB: return Fetch<Word>(); break;
            case ABX: return Fetch<Word>() + X; break;
            case ABY: return Fetch<Word>() + Y; break;
            case IMM: address = PC; PC++; return address; break;
            case ID: address = Fetch<Word>(); return Read<Word>(address); break;
            case IDX: address = Fetch<Byte>(); return Read<Word>(address + X); break;
            case IDY: address = Fetch<Byte>(); return Read<Word>(address) + Y; break;
            case REL: address = PC; PC++; return address; break;
            case ZP: return Fetch<Byte>(); break;
            case ZPX: return Fetch<Byte>() + X; break;
            case ZPY: return Fetch<Byte>() + Y; break;
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
            case ADC: store = Read<Byte>(address) + C; V = (~(A ^ store) & (A ^ (A + store)) & 0x80) > 0; C = V; A = (Byte) (A + store); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case AND: A = A & Read<Byte>(address); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case ASL: store = Read<Byte>(address); C = (store & 0b10000000) > 0; store = store << 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case BCC: store = Read<Byte>(address); if (C == 0) PC += (signed char) store; break;
            case BCS: store = Read<Byte>(address); if (C == 1) PC += (signed char) store; break;
            case BEQ: store = Read<Byte>(address); if (Z == 1) PC += (signed char) store; break;
            case BIT: store = Read<Byte>(address); Z = ((A & store) == 0); N = (store & 0b10000000) > 0; V = (store & 0b01000000) > 0; break;
            case BMI: store = Read<Byte>(address); if (N == 1) PC += (signed char) store; break;
            case BNE: store = Read<Byte>(address); if (Z == 0) PC += (signed char) store; break;
            case BPL: store = Read<Byte>(address); if (N == 0) PC += (signed char) store; break;
            case BRK: Push((Byte) (PC >> 8)); Push((Byte) PC); Push(P); PC = Read<Word>(0xFFFE); B = 1; break;
            case BVC: store = Read<Byte>(address); if (V == 0) PC += (signed char) store; break;
            case BVS: store = Read<Byte>(address); if (V == 1) PC += (signed char) store; break;
            case CLC: C = 0; break;
            case CLD: D = 0; break;
            case CLI: I = 0; break;
            case CLV: V = 0; break;
            case CMP: store = Read<Byte>(address); Z = (A == store); N = ((A - store) & 0b10000000) > 0; C = (A >= store); break;
            case CPX: store = Read<Byte>(address); Z = (X == store); N = ((X - store) & 0b10000000) > 0; C = (X >= store); break;
            case CPY: store = Read<Byte>(address); Z = (Y == store); N = ((Y - store) & 0b10000000) > 0; C = (Y >= store); break;
            case DEC: store = Read<Byte>(address) - 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case DEX: X -= 0x01; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case DEY: Y -= 0x01; Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case EOR: A = (A ^ Read<Byte>(address)); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case INC: store = Read<Byte>(address) + 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case INX: X += 0x01; Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case INY: Y += 0x01; Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case JMP: PC = address; break;
            case JSR: Push((Byte) ((PC - 1) >> 8)); Push((Byte) (PC - 1)); PC = address; break;
            case LDA: A = Read<Byte>(address); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case LDX: X = Read<Byte>(address); Z = (X == 0); N = (X & 0b10000000) > 0; break;
            case LDY: Y = Read<Byte>(address); Z = (Y == 0); N = (Y & 0b10000000) > 0; break;
            case LSR: store = Read<Byte>(address); C = (store & 0b00000001) > 0; store = store >> 1; Write(address, store); Z = (store == 0); N = (store & 0b10000000) > 0; break;
            case NOP: PC++; break;
            case ORA: A = (A | Read<Byte>(address)); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case PHA: Push(A); break;
            case PHP: Push((Byte) P); break;
            case PLA: A = Pull(); Z = (A == 0); N = (A & 0b10000000) > 0; break;
            case PLP: P = Pull(); break;
            case ROL: store = Read<Byte>(address); N = (store & 0b10000000) > 0; store = (store << 1) + C; Write(address, store); Z = (store == 0); C = N; N = (store & 0b10000000) > 0; break;
            case ROR: store = Read<Byte>(address); N = (store & 0b00000001) > 0; store = (store >> 1) | (C << 7); Write(address, store); Z = (store == 0); C = N; N = (store & 0b10000000) > 0; break;
            case RTI: P = Pull(); PC = (Word) Pull(); PC = (Word) (Pull() << 8 | PC); break;
            case RTS: PC = (Word) Pull(); PC = (Word) (Pull() << 8 | PC); break;
            case SBC: store = Read<Byte>(address) + !C; V = ((A ^ store) & (A ^ (A - store)) & 0x80) > 0; C = !V; A = (Byte) (A - store); Z = (A == 0); N = (A & 0b10000000) > 0; break;
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
        Byte OP = Fetch<Byte>();
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