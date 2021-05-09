#include "catch2/catch.hpp"
#include "../constants.hpp"

// STA Test Case

namespace STA {

    void testOne(Mem& mem, CPU& cpu) {

        for (int address = 0x0400; address <= 0x04FF; address++) {
            
            // Reset CPU

            cpu.Reset( mem );
            
            // Run instruction for value at PC

            cpu.STA( mem, (Word) address );
        
            // Assertions
        
            REQUIRE( mem[(Word) address] == cpu.A ); // Ensure value was stored at address
        }
    }

    TEST_CASE( "STA Instruction" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.A.start = (Byte) 0x00;
        config.A.end = (Byte) 0xFF;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode

        Byte OPCodes[8] = { 0xA9, 0xA5, 0xB5, 0xAD, 0xBD, 0xB9, 0xA1, 0xB1 };

        // Vars for script

        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Addressing mode to test

        for (int i = 0; i < length; i++) {
                
            // Reset CPU

            cpu.Reset( mem );

            // Get value at index

            Byte ins = OPCodes[i];

            // Add script

            mem[cpu.PC] = value;
            
            // Run script

            cpu.Run( mem, ins, cpu.PC );
        
            // Assertions
        
            REQUIRE( cpu.A == value ); // Ensure values match up
        }
    }

    TEST_CASE( "LDA Instruction OP Codes" ) {

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