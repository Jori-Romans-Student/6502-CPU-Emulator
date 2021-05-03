#include "catch2/catch.hpp"
#include "../constants.hpp"

// Immediate Test Case Zero Value

TEST_CASE( "LDA Instruction on Zero Value" ) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Instruction

    int amountOfIns = 2;
    Byte Insructions[2] = { 0xA9, 0xA5 };

    // Starting Value

    Byte expectedValue = (Byte) 0x00;

    for (int i = 0; i < amountOfIns; i++) {

        // Fetch expected instruction

        Byte ins = Insructions[i];

        // ========== Script ========== //

        cpu.Reset( mem );

        // ========== Script ========== //

        // Run Instruction

        cpu.Run( mem, ins, expectedValue );

        // Run tests
        
        REQUIRE( cpu.A == expectedValue ); // Ensure values match up
        
        REQUIRE( cpu.N == 0 ); 
        REQUIRE( cpu.Z == 1 ); 

        REQUIRE( cpu.C == 0 );
        REQUIRE( cpu.I == 0 ); 
        REQUIRE( cpu.D == 0 ); 
        REQUIRE( cpu.B == 0 ); 
        REQUIRE( cpu.V == 0 );  
    }
}

// Immediate Test Case Positive Values

TEST_CASE( "LDA Instruction on Positive Value" ) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Instruction

    int amountOfIns = 2;
    Byte Insructions[2] = { 0xA9, 0xA5 };

    for (int i = 0; i < amountOfIns; i++) {

        // Fetch expected instruction

        Byte ins = Insructions[i];

        // Starting Value

        Byte expectedValue = (Byte) 0x01;

        // Amount of runs for test

        int runs = 127;

        // Run for all positive values

        while (runs > 0) {

            // ========== Script ========== //

            cpu.Reset( mem );

            // ========== Script ========== //

            // Run Instruction

            cpu.Run( mem, ins, expectedValue );

            // Run tests
            
            REQUIRE( cpu.A == expectedValue ); // Ensure values match up
            
            REQUIRE( cpu.N == 0 ); 
            REQUIRE( cpu.Z == 0 ); 

            REQUIRE( cpu.C == 0 );
            REQUIRE( cpu.I == 0 ); 
            REQUIRE( cpu.D == 0 ); 
            REQUIRE( cpu.B == 0 ); 
            REQUIRE( cpu.V == 0 );  

            // Subtract amount of runs

            runs--;

            // Increment value

            expectedValue++;
        }
    }
}

// Immediate Test Case Negative Values

TEST_CASE( "LDA Instruction on Negative Value" ) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Instruction

    int amountOfIns = 2;
    Byte Insructions[2] = { 0xA9, 0xA5 };

    for (int i = 0; i < amountOfIns; i++) {

        // Fetch expected instruction

        Byte ins = Insructions[i];

        // Starting Value

        Byte expectedValue = (Byte) 0x80;

        // Amount of runs for test

        int runs = 128;

        // Run for all negative values

        while (runs > 0) {

            // ========== Script ========== //

            cpu.Reset( mem );

            // ========== Script ========== //

            // Run Instruction

            cpu.Run( mem, ins, expectedValue );

            // Run tests
            
            REQUIRE( cpu.A == expectedValue ); // Ensure values match up
            
            REQUIRE( cpu.N == 1 ); 
            REQUIRE( cpu.Z == 0 ); 

            REQUIRE( cpu.C == 0 );
            REQUIRE( cpu.I == 0 ); 
            REQUIRE( cpu.D == 0 ); 
            REQUIRE( cpu.B == 0 ); 
            REQUIRE( cpu.V == 0 );  

            // Subtract amount of runs

            runs--;

            // Increment value

            expectedValue++;
        }
    }
}