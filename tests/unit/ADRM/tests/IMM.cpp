#include "catch2/catch.hpp"
#include "../constants.hpp"

// Immediate Test Case

namespace IMM {

    void test(Mem& mem, CPU& cpu) {

        // Vars for script

        Word PC = cpu.PC;
        Byte value = (Byte) rand();

        // Initialization Script

        mem[PC] = value;

        // Addressing mode to test

        Byte receivedValue = cpu.IMM( mem );

        // Assertions
        
        REQUIRE( receivedValue == value ); // Ensure values match up
        REQUIRE( PC + 1 == cpu.PC ); // Ensure PC was incremented
    }

    TEST_CASE( "Immediate Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF; 

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00;

        // Run Script

        run(&test, config);
    }
}

