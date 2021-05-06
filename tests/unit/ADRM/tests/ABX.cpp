#include "catch2/catch.hpp"
#include "../constants.hpp"

// Absolute X Test Case

namespace ABX {

    void test(Mem& mem, CPU& cpu) {

        // Run loop for every address in 0x03 range

        for (int address = 0x0300; address <= 0x03FF; address++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte X = cpu.X;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = (Byte) (address >> 8);
            mem[PC + 1] = (Byte) address;
            mem[(Word) (address + X)] = value;

            // Addressing mode to test

            Byte receivedValue = cpu.ABX( mem );

            // Assertions
            
            REQUIRE( receivedValue == value ); // Ensure values match up
            REQUIRE( PC + 2 == cpu.PC ); // Ensure PC was incremented twice
        }
    }

    TEST_CASE( "Absolute X Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0xFF; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&test, config);
    }
}