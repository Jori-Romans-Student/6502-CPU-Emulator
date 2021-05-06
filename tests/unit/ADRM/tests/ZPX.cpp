#include "catch2/catch.hpp"
#include "../constants.hpp"

// Zero Page X Test Case

namespace ZPX {

    void test(Mem& mem, CPU& cpu) {

        // Run loop for every ZP Address

        for (int ZPAddress = 0x00; ZPAddress <= 0xFF; ZPAddress++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte X = cpu.X;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = (Byte) ZPAddress;
            mem[(Byte) (ZPAddress + X)] = value;

            // Addressing mode to test

            Byte receivedValue = cpu.ZPX( mem );

            // Assertions
            
            REQUIRE( receivedValue == value ); // Ensure values match up
            REQUIRE( PC + 1 == cpu.PC ); // Ensure PC was incremented
        }
    }

    TEST_CASE( "Zero Page X Addressing Mode" ) {

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