#include <stdio.h>
#include <stdlib.h>
#include <map>

// ========== Types ==========

using Byte = unsigned char;
using Word = unsigned short;

using u32 = unsigned int;

// ========== Hardware ==========

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

    // ========== Addressing Modes ==========

    Byte IMM( Mem& memory ) {

        // Get value and increment PC

        Byte value = memory[PC];
        PC++;

        // Return value

        return value;
    }

    Byte ZP( Mem& memory ) {

        // Fetch Zero Page address at PC

        Byte zero_point_address = IMM( memory );

        // Return byte at zero point address

        return memory[zero_point_address];
    }

    Byte ZPX( Mem& memory ) {

        // Fetch Zero Page address at PC plus X

        Byte zero_point_address = IMM( memory ) + X;

        // Return byte at zero point address

        return memory[zero_point_address];
    }

    Byte ZPY( Mem& memory ) {

        // Fetch Zero Page address at PC plus Y

        Byte zero_point_address = IMM( memory ) + Y;

        // Return byte at zero point address

        return memory[zero_point_address];
    }

    Byte AB( Mem& memory ) {

        // Fetch address at PC

        Word address = (IMM( memory ) << 8) | IMM(memory); // Get next 2 bytes in memory

        // Return byte at address

        return memory[address];
    }

    Byte ABX( Mem& memory ) {

        // Fetch address at PC

        Word address = ((IMM( memory ) << 8) | IMM(memory)) + X; // Get next 2 bytes in memory

        // Return byte at address

        return memory[address];
    }

    Byte ABY( Mem& memory ) {

        // Fetch address at PC

        Word address = ((IMM( memory ) << 8) | IMM(memory)) + Y; // Get next 2 bytes in memory

        // Return byte at address

        return memory[address];
    }

    Byte IDX( Mem& memory ) {

        // Fetch address at PC

        Word addressOfAddress = ((IMM( memory ) << 8) | IMM(memory)) + X; // Get next 2 bytes in memory

        // Fetch address at address

        Byte address = memory[addressOfAddress];

        // Return byte at address

        return memory[address];
    }

    // ========== OP Codes ==========

    Byte RetrieveAddressMode( Mem& memory, Byte ins ) {
        switch( ins ) {
            case 0xA9: {
                return IMM( memory );
            } break;
            case 0xA5: {
                return ZP( memory );
            } break;
            case 0xB5: {
                return ZPX( memory );
            } break;
            case 0xAD: {
                return AB( memory );
            } break;
        }
    }

    // ========== Instructions ==========

    void Run( Mem& memory, Byte ins, Byte value ) {
        switch ( ins ) {
            // LDA
            case 0xA9: case 0xA5: case 0xB5: case 0xAD: {
                
                // Load Accumulator

                A = value;

                // Set Flags

                Z = (A == 0);
                N = (A & 0b10000000) > 0;
            }
        }
    }

    // ========== Operations ==========

    void Execute( Mem& memory ) {
        
        // Get instruction at PC

        Byte instruction = IMM( memory );

        // Retrieve the value to execute the instruction on

        Byte value = RetrieveAddressMode( memory, instruction );

        // Run Instruction

        Run( memory, instruction, value );
    };

    // ========== Scripts ==========

    // Reset script at memory location ** TO BE REMOVED **

    void Reset(Mem& memory) {
        // Boot Up

        PC = 0x0100;
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

        Execute( memory );
    };
};