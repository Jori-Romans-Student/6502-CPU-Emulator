#include "catch2/catch.hpp"
#include "../constants.hpp"

// Immediate Test Case

TEST_CASE( "Zero Page Addressing Mode" ) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Initialize Random Seed

    srand( time(NULL) );

    // Amount of runs for test

    int runs = 256;

    // PC Start

    Word start = (Word) 0x0100;

    while (runs > 0) {

        // ZP Address

        Byte zeroPageAddress = 0x00;

        // ZP Runs

        int zeroPageRuns = 256;

        while (zeroPageRuns > 0 ) {
            
            // ========== Script ========== //

            cpu.Reset( mem );
            cpu.PC = start;
            Byte expectedValue = (Byte) rand();

            mem[start] = zeroPageAddress;
            mem[zeroPageAddress] = expectedValue;

            // ========== Script ========== //

            // Run addressing mode

            Byte value = cpu.ZeroPage( mem );

            // Run tests
        
            REQUIRE( value == expectedValue ); // Ensure values match up
            REQUIRE( start + 1 == cpu.PC ); // Ensure PC was incremented

            // Subtract amount of zeroPageRuns

            zeroPageRuns--;

            // Add zero page address

            zeroPageAddress++;
        }

        // Subtract amount of runs

        runs--;

        // Increment script start

        start++;
    }
}