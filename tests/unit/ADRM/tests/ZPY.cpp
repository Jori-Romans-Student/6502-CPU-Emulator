#include "catch2/catch.hpp"
#include "../constants.hpp"

// Zero Page Y Test Case

namespace ZPY {

    void testOne(Mem& mem, CPU& cpu) {

        // Run loop for every ZP Address

        for (int ZPAddress = 0x00; ZPAddress <= 0xFF; ZPAddress++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte Y = cpu.Y;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = (Byte) ZPAddress;
            mem[(Byte) (ZPAddress + Y)] = value;

            // Addressing mode to test

            Word receivedAddress = cpu.ZPY( mem );

            // Assertions
            
            REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Zero Page Y Addressing Mode" ) {

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

        Byte OPCodes[1] = { 0xB6 };

        // Vars for script

        Word ZPAddress = 0x00;
        Word PC = cpu.PC;
        Byte Y = cpu.Y;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = (Byte) ZPAddress;
        mem[(Byte) (ZPAddress + Y)] = value;

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

    TEST_CASE( "Zero Page Y Addressing Mode OP Codes" ) {

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