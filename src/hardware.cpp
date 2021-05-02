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

    // Instructions;

    static constexpr Byte INS_LDA_IM = 0xA9;
    static constexpr Byte INS_LDA_ZP = 0xA5;

    // Actions

    Byte Read( Mem& memory, Word address ) {
        Byte data = memory[address];
        return data;
    }

    Byte Fetch( Mem& memory ) {
        Byte data = Read(memory, PC);
        PC++;
        return data;
    }

    void Execute( Mem& memory, Byte instruction ) {
        switch (instruction) {
            case INS_LDA_IM: {

                // Fetch value from PC that will contain actual value instead of pointer

                Byte value = Fetch( memory );

                // Load Accumulator

                A = value;

                // Set Flags

                Z = (A == 0);
                N = (A & 0b10000000) > 0;

            } break;
            case INS_LDA_ZP: {

                // Fetch ZP Address from next PC then get value from address

                Byte zero_point_address = Fetch( memory );
                Byte value = Read( memory, zero_point_address );

                // Load Accumulator

                A = value;

                // Set Flags

                Z = (A == 0);
                N = (A & 0b10000000) > 0;

            } break;
            default: {
                
            }
        }
    };

    // Reset script at memory location ** TO BE REMOVED **

    void Reset(Mem& memory) {
        // Boot Up

        PC = 0x0000;
        SP = 0x00;
        D = 0;
        A = X = Y = 0;
        C = Z = I = D = B = V = N = 0;

        memory.Initialize();
    };

    // Start a script at memory location ** TO BE REMOVED **

    void Start(Mem& memory, Word address) {

        // Set Program Counter to Address

        PC = address;
        
        // Fetch instruction from memory

        Byte instruction = Fetch( memory );

        // Execute instruciton

        Execute( memory, instruction );
    };
};