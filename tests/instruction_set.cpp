#include "catch2/catch.hpp"
#include "../src/hardware.cpp"

Mem mem;
CPU cpu;

Byte instruction = CPU::INS_LDA_IM;

void LoadProgram( Byte value ) {
    mem[0xFFFC] = instruction; // Sets the instruction at the PC
    mem[0xFFFD] = value; // Immediate next value, which should be loaded to A
};

TEST_CASE( "LDA Immediate Instruction" ) {
    
    // Reset memory and PC each test

    cpu.Reset( mem );

    SECTION( "should have proper OP Code" ) {
        REQUIRE ( instruction == 0xA9 );
    }

    SECTION( "should run small script correctly wtih zero value" ) {
        
        // Immediate Byte to Load

        Byte value = 0x00;

        // Assembly Program

        LoadProgram( value );

        // Execute Program

        cpu.Execute( mem, 2 ); 

        // Run Assertions on Non Affected Flags

        REQUIRE( cpu.C == 0 ); 
        REQUIRE( cpu.I == 0 ); 
        REQUIRE( cpu.D == 0 ); 
        REQUIRE( cpu.B == 0 ); 
        REQUIRE( cpu.V == 0 );

        // Run Assertion on Zero Flag

        REQUIRE( cpu.Z == 1);

        // Run Assertion on Negative Flag

        REQUIRE( cpu.N == 0 ); 

        // Run Assertion on A Register to ensure proper load

        REQUIRE( cpu.A == value );

    }

    SECTION( "should run small script correctly wtih negative value" ) {
        
        // Immediate Byte to Load

        Byte value = 0xFF;

        // Assembly Program

        LoadProgram( value );

        // Execute Program

        cpu.Execute( mem, 2 ); 

        // Run Assertions on Non Affected Flags

        REQUIRE( cpu.C == 0 ); 
        REQUIRE( cpu.I == 0 ); 
        REQUIRE( cpu.D == 0 ); 
        REQUIRE( cpu.B == 0 ); 
        REQUIRE( cpu.V == 0 );

        // Run Assertion on Zero Flag

        REQUIRE( cpu.Z == 0 );

        // Run Assertion on Negative Flag

        REQUIRE( cpu.N == 1 ); 

        // Run Assertion on A Register to ensure proper load

        REQUIRE( cpu.A == value );

    }

    SECTION( "should run small script correctly wtih positive value" ) {
        
        // Immediate Byte to Load

        Byte value = 0x65;

        // Assembly Program

        LoadProgram( value );

        // Execute Program

        cpu.Execute( mem, 2 ); 

        // Run Assertions on Non Affected Flags

        REQUIRE( cpu.C == 0 ); 
        REQUIRE( cpu.I == 0 ); 
        REQUIRE( cpu.D == 0 ); 
        REQUIRE( cpu.B == 0 ); 
        REQUIRE( cpu.V == 0 );

        // Run Assertion on Zero Flag

        REQUIRE( cpu.Z == 0 );

        // Run Assertion on Negative Flag

        REQUIRE( cpu.N == 0 ); 

        // Run Assertion on A Register to ensure proper load

        REQUIRE( cpu.A == value );

    }
}