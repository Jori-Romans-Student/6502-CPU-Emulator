#include <stdio.h>
#include <stdlib.h>

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

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
};

struct CPU {
    
    // Progarm Counter and Stack Pointer

    Word PC;
    Byte SP;

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

    void Reset(Mem& memory) {
        // Boot Up

        PC = 0xFFFC;
        SP = 0x00;
        D = 0;
        A = X = Y = 0;
        C = Z = I = D = B = V = N = 0;

        memory.Initialize();
    }

    Byte Read(Mem& memory, u32& cycles) {
        Byte data = memory[PC];
        cycles--;
        return data;
    }

    Byte Fetch(Mem& memory, u32& cycles) {
        Byte data = Read(memory, cycles);
        PC++;
        return data;
    }

    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0xA5;

    void Execute(Mem& memory, u32 cycles) {
        while ( cycles > 0 ) {
            Byte instruction = Fetch( memory, cycles );
            switch (instruction) {
                case INS_LDA_IM: {
                    Byte value = Fetch( memory, cycles );
                    A = value;
                    Z = (A == 0);
                    N = (A & 0b10000000) > 0;
                } break;
                default: {
                  
                }
            }
        }
    }
};

int main() {
  Mem mem;
  CPU cpu;
  cpu.Reset( mem );

  // Program

  mem[0xFFFC] = CPU::INS_LDA_ZP;
  mem[0xFFFD] = 0x42;

  cpu.Execute( mem, 2 );
  return 0;
}
