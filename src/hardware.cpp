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

            // Absolute Addressing Mode

            case 0xAD: case 0xAE: case 0xAC: case 0x6D: case 0x2D: 
            case 0x0E: case 0x2C: case 0xCD: case 0xEC: case 0xCC:
            case 0xCE: case 0x4D: case 0xEE: case 0x4C: case 0x20: 
            case 0x4E: case 0x0D: case 0x2E: case 0x6E: case 0xED: 
            case 0x8D: case 0x8E: 
            {
                return AB( memory );
            } 
            break;

            // Absolute X Addressing Mode

            case 0xBD: case 0xBC: case 0x7D: case 0x3D: case 0x1E: 
            case 0xDD: case 0xDE: case 0x5D: case 0xFE: case 0x5E: 
            case 0x1D: case 0x3E: case 0x7E: case 0xFD: case 0x9D: 
            {
                return ABX( memory );
            } 
            break;

            // Absolute Y Addressing Mode

            case 0xB9: case 0xBE: case 0x79: case 0x39: case 0xD9: 
            case 0x59: case 0x19: case 0xF9: case 0x99: 
            {
                return ABY( memory );
            } 
            break;

            // Indexed Indirect Addressing Mode

            case 0xA1: case 0x61: case 0x21: case 0xC1: case 0x41: 
            case 0x01: case 0xE1: case 0x81:
            {
                return IDX( memory );
            } 
            break;

            // Indirect Indexed Addressing Mode

            case 0xB1: case 0x71: case 0x31: case 0xD1: case 0x51:
            case 0x11: case 0xF1: case 0x91:
            {
                return IDY( memory );
            } 
            break;

            // Immediate Addressing Mode

            case 0xA9: case 0xA2: case 0xA0: case 0x69: case 0x29:
            case 0xC9: case 0xE0: case 0xC0: case 0x49: case 0x09:
            case 0xE9:
            {
                return IMM( memory );
            } 
            break;

            // Zero Page Addressing Mode

            case 0xA5: case 0xA6: case 0xA4: case 0x65: case 0x25:
            case 0x06: case 0x24: case 0xC5: case 0xE4: case 0xC4:
            case 0xC6: case 0x45: case 0xE6: case 0x46: case 0x05:
            case 0x26: case 0x66: case 0xE5: case 0x85: case 0x86:
            case 0x84: 
            {
                return ZP( memory );
            } 
            break;

            // Zero Page X Addressing Mode

            case 0xB5: case 0xB4: case 0x75: case 0x35: case 0x16:
            case 0xD5: case 0xD6: case 0x55: case 0xF6: case 0x56:
            case 0x15: case 0x36: case 0x76: case 0xF5: case 0x95:
            case 0x94:
            {
                return ZPX( memory );
            } 
            break;

            // Zero Page Y Addressing Mode

            case 0xB6: case 0x96:
            {
                return ZPY( memory );
            } 
            break;

            // Default (should not be triggered)

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

    void STA( Mem& memory, Word address ) {
        memory[address] = A;
    }

    void STX( Mem& memory, Word address ) {
        memory[address] = X;
    }

    void Run( Mem& memory, Byte ins, Word address ) {

        switch ( ins ) {

            // LDA Instruction
            
            case 0xA9: case 0xA5: case 0xB5: case 0xAD: case 0xBD: 
            case 0xB9: case 0xA1: case 0xB1: 
            {
                LDA( memory, address );
            } 
            break;

            // LDX Instruction

            case 0xA2: case 0xA6: case 0xB6: case 0xAE: case 0xBE: 
            {
                LDX( memory, address );
            } 
            break;

            // LDY Instruction

            case 0xA0: case 0xA4: case 0xB4: case 0xAC: case 0xBC: 
            {
                LDY( memory, address );
            } 
            break;

            // STA Instruction

            case 0x85: case 0x95: case 0x8D: case 0x9D: case 0x99:
            case 0x81: case 0x91:
            {
                STA( memory, address );
            }
            break;

            // STX Instruction

            case 0x86: case 0x96: case 0x8E:
            {
                STX( memory, address );
            }
            break;
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