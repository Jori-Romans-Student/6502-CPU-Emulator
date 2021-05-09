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

            Byte receivedValue = cpu.ZP( mem );

            // Assertions
            
            REQUIRE( receivedValue == value ); // Ensure values match up
        }
    }

    TEST_CASE( "Zero Page Addressing Mode" ) {

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

        Byte OPCodes[1] = {0xAD};

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

            Byte receivedValue = cpu.RetrieveAddressMode( mem, code );
        
            // Assertions
        
            REQUIRE( receivedValue == value ); // Ensure values match up
        }
    }

    TEST_CASE("Zero Page Mode OP Codes") {

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