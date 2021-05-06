#include "catch2/catch.hpp"
#include "../constants.hpp"

// Indirect Indexed Test Case

namespace IDX {

    void test(Mem& mem, CPU& cpu) {

        // Run loop for PC on first 16 addresses in 0x03 range

        for (int PCAddress = 0x0400; PCAddress <= 0x040F; PCAddress++) {
            
            // Run loop for value address on first 16 addresses in zero page

            for (int valueAddress = 0x00; valueAddress <= 0x0F; valueAddress++) {
                
                // Vars for script

                Word PC = cpu.PC;
                Byte X = cpu.X;
                Byte value = (Byte) rand();

                // Initialization Script

                mem[PC] = (Byte) (PCAddress >> 8);
                mem[PC + 1] = (Byte) PCAddress;
                mem[(Word) (PCAddress + X)] = (Byte) valueAddress;
                mem[(Byte) valueAddress] = value;

                // Addressing mode to test

                Byte receivedValue = cpu.IDX( mem );

                // Assertions
                
                REQUIRE( receivedValue == value ); // Ensure values match up
                REQUIRE( PC + 2 == cpu.PC ); // Ensure PC was incremented twice
            }
        }
    }

    TEST_CASE( "Indexed Indirect Addressing Mode" ) {

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