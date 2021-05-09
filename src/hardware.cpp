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

    Word IMM( Mem& memory ) {

        // Get value and increment PC

        Word address = PC;
        PC++;

        // Return value

        return address;
    }

    Byte ZP( Mem& memory ) {

        // Fetch Zero Page address address at PC

        Word addressOfAddress = IMM( memory );

        // Return zero point address

        return (Byte) memory[addressOfAddress];
    }

    Byte ZPX( Mem& memory ) {

        // Fetch Zero Page address address at PC

        Word addressOfAddress = IMM( memory );

        // Return zero point address plus X

        return (Byte) (memory[addressOfAddress] + X);
    }

    Byte ZPY( Mem& memory ) {

        // Fetch Zero Page address address at PC

        Word addressOfAddress = IMM( memory );

        // Return zero point address plus X

        return (Byte) (memory[addressOfAddress] + Y);
    }

    Word AB( Mem& memory ) {

        // Fetch address at PC

        Word address = (memory[IMM( memory )] << 8) | memory[IMM( memory )]; // Get next 2 bytes in memory

        // Return address

        return address;
    }

    Word ABX( Mem& memory ) {

        // Fetch address at PC

        Word address = ((memory[IMM( memory )] << 8) | memory[IMM(memory)]); // Get next 2 bytes in memory

        // Return address + X

        return address + X;
    }

    Word ABY( Mem& memory ) {

        // Fetch address at PC

        Word address = ((memory[IMM( memory )] << 8) | memory[IMM(memory)]); // Get next 2 bytes in memory

        // Return address + Y

        return address + Y;
    }

    Word IDX( Mem& memory ) {

        // Fetch address at PC

        Byte addressOfAddress = memory[IMM( memory )];

        // Fetch address at address

        Word address = (Word) ((memory[(Byte) (addressOfAddress + X)] << 8) | memory[(Byte) (addressOfAddress + 1 + X)]);

        // Return address

        return address;
    }

    Word IDY( Mem& memory ) {

        // Fetch address at PC

        Byte addressOfAddress = memory[IMM( memory )];

        // Fetch address at address

        Word address = (Word) (((memory[addressOfAddress] << 8) | memory[(Byte) (addressOfAddress + 1)]) + Y);

        // Return address

        return address;
    }

    // ========== OP Codes ==========

    Word RetrieveAddressMode( Mem& memory, Byte ins ) {
        switch( ins ) {
            case 0xAD: case 0xAE: case 0xAC: {
                return AB( memory );
            } break;
            case 0xBD: case 0xBC: {
                return ABX( memory );
            } break;
            case 0xB9: case 0xBE: {
                return ABY( memory );
            } break;
            case 0xA9: case 0xA2: case 0xA0: {
                return IMM( memory );
            } break;
            case 0xA1: {
                return IDX( memory );
            } break;
            case 0xB1: {
                return IDY( memory );
            } break;
            case 0xA5: case 0xA6: case 0xA4: {
                return ZP( memory );
            } break;
            case 0xB5: case 0xB4: {
                return ZPX( memory );
            } break;
            case 0xB6: {
                return ZPY( memory );
            } break;
            default: {
                return (Byte) 0x00;
            }
        }
    }

    // ========== Instructions ==========

    void LDA( Mem& memory, Word address ) {
        // Load Accumulator

        A = memory[address];

        // Set Flags

        Z = (A == 0);
        N = (A & 0b10000000) > 0;
    }

    void LDX( Mem& memory, Word address ) {
        // Load X Register

        X = memory[address];

        // Set Flags

        Z = (X == 0);
        N = (X & 0b10000000) > 0;
    }

    void LDY( Mem& memory, Word address ) {
        // Load Y Register

        Y = memory[address];

        // Set Flags

        Z = (Y == 0);
        N = (Y & 0b10000000) > 0;
    }

    void Run( Mem& memory, Byte ins, Word address ) {
        switch ( ins ) {

            // LDA
            
            case 0xA9: case 0xA5: case 0xB5: case 0xAD: case 0xBD: case 0xB9: case 0xA1: case 0xB1: {
                LDA( memory, address );
            } break;

            // LDX

            case 0xA2: case 0xA6: case 0xB6: case 0xAE: case 0xBE: {
                LDX( memory, address );
            } break;

            // LDX

            case 0xA0: case 0xA4: case 0xB4: case 0xAC: case 0xBC: {
                LDY( memory, address );
            } break;
        }
    }

    // ========== Operations ==========

    void Execute( Mem& memory ) {
        
        // Get instruction at PC

        Byte instruction = memory[IMM( memory )];

        // Retrieve the value to execute the instruction on

        Word address = RetrieveAddressMode( memory, instruction );

        // Run Instruction

        Run( memory, instruction, address );
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