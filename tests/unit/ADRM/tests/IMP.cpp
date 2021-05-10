#include "catch2/catch.hpp"
#include "../constants.hpp"

// Implied Test Case

namespace IMP {

    void testOne(Mem& mem, CPU& cpu) {

        // Addressing mode to test

        Byte receivedAddress = cpu.IMP( mem );

        // Assertions
        
        REQUIRE( receivedAddress == (Byte) 0x00 ); // Ensure 0x00 address is returned
    }

    TEST_CASE( "Implied Addressing Mode" ) {

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

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for Implied Address Mode

        Byte OPCodes[25] = { 
            0x00, 0x18, 0xD8, 0x58, 0xB8, 
            0xCA, 0x88, 0xE8, 0xC8, 0xEA,
            0x48, 0x08, 0x68, 0x28, 0x40,
            0x60, 0x38, 0xF8, 0x78, 0xAA,
            0xA8, 0xBA, 0x8A, 0x9A, 0x98
        };

        // Vars for script

        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        // Addressing mode to test

        for (int i = 0; i < length; i++) {

            // Get value at index

            Byte code = OPCodes[i];
            
            // Get value

            Word receivedAddress = cpu.RetrieveAddressMode( mem, code );
        
            // Assertions
        
            REQUIRE( receivedAddress == (Word) 0x00 ); // Ensure 0x00 address is returned
        }
    }

    TEST_CASE( "Implied Addressing Mode OP Codes" ) {

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

