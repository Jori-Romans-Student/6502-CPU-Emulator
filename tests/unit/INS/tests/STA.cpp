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

        Byte OPCodes[7] = { 
            0x85, 0x95, 0x8D, 0x9D, 0x99,
            0x81, 0x91
        };

        // Vars for script

        Word address = 0x0400;
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Addressing mode to test

        for (int i = 0; i < length; i++) {
                
            // Reset CPU

            cpu.Reset( mem );
            cpu.A = (Byte) rand();

            // Get value at index

            Byte ins = OPCodes[i];
            
            // Run script

            cpu.Run( mem, ins, address );
        
            // Assertions
        
            REQUIRE( mem[address] == cpu.A ); // Ensure value stored at address
        }
    }

    TEST_CASE( "STA Instruction OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.A.start = (Byte) 0x00;
        config.A.end = (Byte) 0x00; 

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testTwo, config);
    }
}