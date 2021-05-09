#include "catch2/catch.hpp"
#include "../constants.hpp"

// STY Test Case

namespace STY {

    void testOne(Mem& mem, CPU& cpu) {

        for (int address = 0x0400; address <= 0x04FF; address++) {
            
            // Reset CPU

            cpu.Reset( mem );
            
            // Run instruction for value at PC

            cpu.STY( mem, (Word) address );
        
            // Assertions
        
            REQUIRE( mem[(Word) address] == cpu.Y ); // Ensure value was stored at address
        }
    }

    TEST_CASE( "STY Instruction" ) {

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
        config.Y.end = (Byte) 0xFF; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for STY Instruction

        Byte OPCodes[3] = { 
            0x84, 0x94, 0x8C
        };

        // Vars for script

        Word address = 0x0400;
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Addressing mode to test

        for (int i = 0; i < length; i++) {
                
            // Reset CPU

            cpu.Reset( mem );
            cpu.Y = (Byte) rand();

            // Get value at index

            Byte ins = OPCodes[i];
            
            // Run script

            cpu.Run( mem, ins, address );
        
            // Assertions
        
            REQUIRE( mem[address] == cpu.Y ); // Ensure value stored at address
        }
    }

    TEST_CASE( "STY Instruction OP Codes" ) {

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