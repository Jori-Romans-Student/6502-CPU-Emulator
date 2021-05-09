#include "catch2/catch.hpp"
#include "../constants.hpp"

// Indirect Indexed Test Case

namespace IDX {

    void testOne(Mem& mem, CPU& cpu) {

        // Run loop for PC on first 16 addresses in 0x03 range

        for (int PCAddress = 0x00; PCAddress <= 0x0F; PCAddress++) {
            
            // Run loop for value address on first 16 addresses in zero page

            for (int effectiveAddress = 0x0400; effectiveAddress <= 0x040F; effectiveAddress++) {
                
                // Vars for script

                Word PC = cpu.PC;
                Byte X = cpu.X;
                Byte value = (Byte) rand();

                // Initialization Script

                mem[PC] = (Byte) PCAddress;
                mem[(Byte) (PCAddress + X)] = (Byte) (effectiveAddress >> 8);
                mem[(Byte) (PCAddress + X + 1)] = (Byte) (effectiveAddress);
                mem[(Word) effectiveAddress] = value;

                // Addressing mode to test

                Word receivedAddress = cpu.IDX( mem );

                // Assertions
                
                REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
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

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode

        Byte OPCodes[1] = {0xA1};

        // Vars for script

        Word PCAddress = 0x00;
        Word effectiveAddress = 0x0400;
        Word PC = cpu.PC;
        Byte X = cpu.X;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = (Byte) PCAddress;
        mem[(Byte) (PCAddress + X)] = (Byte) (effectiveAddress >> 8);
        mem[(Byte) (PCAddress + X + 1)] = (Byte) (effectiveAddress);
        mem[(Word) effectiveAddress] = value;

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

    TEST_CASE( "Indexed Indirect Addressing Mode OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.X.start = (Byte) rand();
        config.X.end = config.X.start; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testTwo, config);
    }
}