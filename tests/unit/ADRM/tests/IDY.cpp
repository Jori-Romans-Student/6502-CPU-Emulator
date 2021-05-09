#include "catch2/catch.hpp"
#include "../constants.hpp"

// Indirect Indexed Test Case

namespace IDY {

    void testOne(Mem& mem, CPU& cpu) {

        // Run loop for first 16 addresses in 0x00 range

        for (int PCAddress = 0x00; PCAddress <= 0x0F; PCAddress++) {

            for (int effectiveAddress = 0x0500; effectiveAddress <= 0x050F; effectiveAddress++) {
                
                // Vars for script

                Word PC = cpu.PC;
                Byte X = cpu.X;
                Byte Y = cpu.Y;
                Byte value = (Byte) rand();

                // Initialization Script

                mem[PC] = (Byte) (PCAddress);
                mem[(Byte) (PCAddress)] = (Byte) ((effectiveAddress - Y) >> 8);
                mem[(Byte) (PCAddress + 1)] = (Byte) (effectiveAddress - Y);
                mem[(Word) effectiveAddress] = value;

                // Addressing mode to test

                Word receivedAddress = cpu.IDY( mem );

                // Assertions
                
                REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
            }
        }
    }

    TEST_CASE( "Indirect Indexed Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0xFF; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode Y

        Byte OPCodes[1] = {0xB1};

        // Vars for script

        Byte PCAddress = 0x00;
        Word effectiveAddress = 0x0500;
        Word PC = cpu.PC;
        Byte Y = cpu.Y;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = (Byte) (PCAddress);
        mem[(Byte) (PCAddress)] = (Byte) ((effectiveAddress - Y) >> 8);
        mem[(Byte) (PCAddress + 1)] = (Byte) (effectiveAddress - Y);
        mem[(Word) effectiveAddress] = value;

        // Addressing mode to test

        for (int i = 0; i < length; i++) {

            // Get value at index

            Byte code = OPCodes[i];

            // Reset PC

            cpu.PC = PC;
            
            // Get value

            Word receivedAddress = cpu.RetrieveAddressMode( mem, code );
        
            // Assertions
        
            REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Indirect Indexed Addressing Mode OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) rand();
        config.Y.end = config.Y.start;

        // Run Script

        run(&testTwo, config);
    }
}