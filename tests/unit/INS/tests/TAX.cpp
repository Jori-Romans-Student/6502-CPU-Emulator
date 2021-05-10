#include "catch2/catch.hpp"
#include "../constants.hpp"

// TAX Test Case

namespace TAX {

    void testOne(Mem& mem, CPU& cpu) {

        cpu.TAX( mem );
    
        // Assertions
    
        REQUIRE( cpu.X == cpu.A );

        if ( cpu.X >= 0x80 ) {
            REQUIRE( cpu.N == 1 );
        }
        else {
            REQUIRE( cpu.N == 0 );
        }

        if ( cpu.X == 0x00 ) {
            REQUIRE( cpu.Z == 1 );
        }
        else {
            REQUIRE( cpu.Z == 0 );
        } 
    }

    TEST_CASE( "TAX Instruction" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.A.start = (Byte) 0x00;
        config.A.end = (Byte) 0xFF;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for TAX Instruction

        Byte OPCodes[1] = { 
            0xAA
        };

        // Vars for script

        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));
        Byte A = cpu.A;

        // Addressing mode to test

        for (int i = 0; i < length; i++) {
                
            // Reset CPU

            cpu.Reset( mem );
            cpu.A = A;

            // Get value at index

            Byte ins = OPCodes[i];
            
            // Run script

            cpu.Run( mem, ins, cpu.PC );
        
            // Assertions
        
            REQUIRE( cpu.X == cpu.A ); // Ensure values match up

            if ( cpu.X >= 0x80 ) {
                REQUIRE( cpu.N == 1 );
            }
            else {
                REQUIRE( cpu.N == 0 );
            }

            if ( cpu.X == 0x00 ) {
                REQUIRE( cpu.Z == 1 );
            }
            else {
                REQUIRE( cpu.Z == 0 );
            } 
        }
    }

    TEST_CASE( "TAX Instruction OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.A.start = (Byte) rand();
        config.A.end = config.A.start;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00; 

        config.Y.start = (Byte) 0x00;
        config.Y.end = (Byte) 0x00; 

        // Run Script

        run(&testTwo, config);
    }
}