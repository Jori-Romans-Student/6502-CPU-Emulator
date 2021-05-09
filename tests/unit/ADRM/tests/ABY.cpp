#include "catch2/catch.hpp"
#include "../constants.hpp"

// Absolute Y Test Case

namespace ABY {

    void testOne(Mem& mem, CPU& cpu) {

        // Run loop for every address in 0x03 range

        for (int address = 0x0300; address <= 0x03FF; address++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte Y = cpu.Y;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = (Byte) (address >> 8);
            mem[PC + 1] = (Byte) address;
            mem[(Word) (address + Y)] = value;

            // Addressing mode to test

            Byte receivedValue = cpu.ABY( mem );

            // Assertions
            
            REQUIRE( receivedValue == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Absolute Y Addressing Mode" ) {

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

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode Y

        Byte OPCodes[1] = {0xB9};

        // Vars for script

        Word address = 0x0300;
        Word PC = cpu.PC;
        Byte Y = cpu.Y;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = (Byte) (address >> 8);
        mem[PC + 1] = (Byte) address;
        mem[(Word) (address + Y)] = value;

        // Addressing mode to test

        for (int i = 0; i < length; i++) {

            // Get value at index

            Byte code = OPCodes[i];

            // Reset PC

            cpu.PC = PC;
            
            // Get value

            Byte receivedValue = cpu.RetrieveAddressMode( mem, code );
        
            // Assertions
        
            REQUIRE( receivedValue == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Absolute Y Addressing Mode OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) rand();
        config.Y.end = config.Y.start; 

        // Run Script

        run(&testTwo, config);
    }
}