#include "catch2/catch.hpp"
#include "../constants.hpp"

// Zero Page Test Case

namespace ZP {

    void testOne(Mem& mem, CPU& cpu) {

        // Run loop for every ZP Address

        for (int ZPAddress = 0x00; ZPAddress <= 0xFF; ZPAddress++) {

            // Vars for script

            Word PC = cpu.PC;
            Byte value = (Byte) rand();

            // Initialization Script

            mem[PC] = (Byte) ZPAddress;
            mem[(Byte) ZPAddress] = value;

            // Addressing mode to test

            Word receivedAddress = cpu.ZP( mem );

            // Assertions
            
            REQUIRE( mem[receivedAddress] == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Zero Page Addressing Mode" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x01FF;

        config.A.start = (Byte) 0x00;
        config.A.end = (Byte) 0x00;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Absolute Addressing Mode

        Byte OPCodes[21] = { 
            0xA5, 0xA6, 0xA4, 0x65, 0x25,
            0x06, 0x24, 0xC5, 0xE4, 0xC4,
            0xC6, 0x45, 0xE6, 0x46, 0x05,
            0x26, 0x66, 0xE5, 0x85, 0x86, 
            0x84
        };

        // Vars for script

        Word ZPAddress = 0x00;
        Word PC = cpu.PC;
        Byte value = (Byte) rand();
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Initialization Script

        mem[PC] = (Byte) ZPAddress;
        mem[(Byte) ZPAddress] = value;

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

    TEST_CASE("Zero Page Mode OP Codes") {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.A.start = (Byte) 0x00;
        config.A.end = (Byte) 0x00;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testTwo, config);
    }
}