#include "catch2/catch.hpp"
#include "../constants.hpp"

// Immediate Test Case

namespace IMM {

    void testOne(Mem& mem, CPU& cpu) {

        // Vars for script

        Word PC = cpu.PC;
        Byte value = (Byte) rand();

        // Initialization Script

        mem[PC] = value;

        // Addressing mode to test

        Word receivedAddress = cpu.IMM( mem );

        // Assertions
        
        REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
    }

    TEST_CASE( "Immediate Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF; 

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00;

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode

        Byte OPCodes[11] = { 
            0xA9, 0xA2, 0xA0, 0x69, 0x29,
            0xC9, 0xE0, 0xC0, 0x49, 0x09,
            0xE9
        };

        // Vars for script

        Word PC = cpu.PC;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = value;

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

    TEST_CASE( "Immediate Addressing Mode OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100; 

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00;

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testTwo, config);
    }
}

