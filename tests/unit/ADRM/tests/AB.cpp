#include "catch2/catch.hpp"
#include "../constants.hpp"

// Absolute Test Case

namespace AB {

    void testOne(Mem& mem, CPU& cpu) {

        // Run loop for every address in 0x03 range

        for (int address = 0x0300; address <= 0x03FF; address++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = (Byte) (address >> 8);
            mem[PC + 1] = (Byte) address;
            mem[(Word) address] = value;

            // Addressing mode to test

            Word receivedAddress = cpu.AB( mem );

            // Assertions
            
            REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Absolute Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode

        Byte OPCodes[22] = { 
            0xAD, 0xAE, 0xAC, 0x6D, 0x2D,
            0x0E, 0x2C, 0xCD, 0xEC, 0xCC,
            0xCE, 0x4D, 0xEE, 0x4C, 0x20,
            0x4E, 0x0D, 0x2E, 0x6E, 0xED,
            0x8D, 0x8E
        };

        // Vars for script

        Word address = 0x0300;
        Word PC = cpu.PC;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = (Byte) (address >> 8);
        mem[PC + 1] = (Byte) address;
        mem[address] = value;

        // Addressing mode to test

        for (int i = 0; i < length; i++) {

            // Get value at index

            Byte code = OPCodes[i];

            // Reset PC

            cpu.PC = PC;
            
            // Get address

            Word receivedAddress = cpu.RetrieveAddressMode( mem, code );
        
            // Assertions
        
            REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
        }
    }

    TEST_CASE("Absolute Addressing Mode OP Codes") {

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