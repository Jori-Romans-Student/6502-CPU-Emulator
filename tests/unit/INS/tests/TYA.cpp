#include "catch2/catch.hpp"
#include "../constants.hpp"

// TYA Test Case

namespace TYA {

    void testOne(Mem& mem, CPU& cpu) {

        cpu.TYA( mem );
    
        // Assertions
    
        REQUIRE( cpu.A == cpu.Y );

        if ( cpu.A >= 0x80 ) {
            REQUIRE( cpu.N == 1 );
        }
        else {
            REQUIRE( cpu.N == 0 );
        }

        if ( cpu.A == 0x00 ) {
            REQUIRE( cpu.Z == 1 );
        }
        else {
            REQUIRE( cpu.Z == 0 );
        } 
    }

    TEST_CASE( "TYA Instruction" ) {

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
        config.Y.end = (Byte) 0xFF; 

        // Run Script

        run(&testOne, config);
    }

    void testTwo(Mem& mem, CPU& cpu) {

        // OPCodes for TYA Instruction

        Byte OPCodes[1] = { 
            0x98
        };

        // Vars for script

        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));
        Byte Y = cpu.Y;

        // Addressing mode to test

        for (int i = 0; i < length; i++) {
                
            // Reset CPU

            cpu.Reset( mem );
            cpu.Y = Y;

            // Get value at index

            Byte ins = OPCodes[i];
            
            // Run script

            cpu.Run( mem, ins, cpu.PC );
        
            // Assertions
        
            REQUIRE( cpu.A == cpu.Y );

            if ( cpu.A >= 0x80 ) {
                REQUIRE( cpu.N == 1 );
            }
            else {
                REQUIRE( cpu.N == 0 );
            }

            if ( cpu.A == 0x00 ) {
                REQUIRE( cpu.Z == 1 );
            }
            else {
                REQUIRE( cpu.Z == 0 );
            } 
        }
    }

    TEST_CASE( "TYA Instruction OP Codes" ) {

        // CPU Config

        CPUConfig config;

        // Ranges for Tests

        config.PC.start = (Word) 0x0100;
        config.PC.end = (Word) 0x0100;

        config.A.start = (Byte) 0x00;
        config.A.end = (Byte) 0x00;

        config.X.start = (Byte) 0x00;
        config.X.end = (Byte) 0x00;

        config.Y.start = (Byte) rand();
        config.Y.end = config.Y.start; 

        // Run Script

        run(&testTwo, config);
    }
}