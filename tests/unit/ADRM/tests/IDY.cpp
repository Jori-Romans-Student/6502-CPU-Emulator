#include "catch2/catch.hpp"
#include "../constants.hpp"

// Indirect Indexed Test Case

namespace IDY {

    void test(Mem& mem, CPU& cpu) {

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

                Byte receivedValue = cpu.IDY( mem );

                // Assertions
                
                REQUIRE( receivedValue == value ); // Ensure values match up
                REQUIRE( PC + 1 == cpu.PC ); // Ensure PC was incremented twice
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

        run(&test, config);
    }
}