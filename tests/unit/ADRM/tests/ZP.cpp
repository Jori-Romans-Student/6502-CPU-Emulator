#include "catch2/catch.hpp"
#include "../constants.hpp"

// Zero Page Test Case

namespace ZP {

    void test(Mem& mem, CPU& cpu) {

        // Run loop for every ZP Address

        for (Byte ZPAddress = 0x00; ZPAddress < 0xFF; ZPAddress++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = ZPAddress;
            mem[ZPAddress] = value;

            // Addressing mode to test

            Byte receivedValue = cpu.ZP( mem );

            // Assertions
            
            REQUIRE( receivedValue == value ); // Ensure values match up
            REQUIRE( PC + 1 == cpu.PC ); // Ensure PC was incremented
        }
    }

    TEST_CASE( "Zero Page Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF; 

        // Run Script

        run(&test, config);
    }
}