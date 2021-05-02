#include "catch2/catch.hpp"
#include "../../../../src/hardware.cpp"

// Initialize Memory and CPU

Mem mem;
CPU cpu;

// Extract constant codes from CPU

Byte INS_LDA_IM = CPU::INS_LDA_IM;
Byte INS_LDA_ZP = CPU::INS_LDA_ZP;

// LDA_IM Test Case

TEST_CASE( "LDA Immediate Instruction" ) {
    
    // Reset memory and PC each test

    cpu.Reset( mem );

    SECTION( "should have proper OP Code" ) {
        REQUIRE ( INS_LDA_IM == 0xA9 );
    }

    SECTION( "should run script correctly with zero value" ) {
        
        // Immediate Byte to Load

        Byte value = 0x00;

        // Assembly Program

        mem[0x0000] = INS_LDA_IM; // Sets the instruction at the PC
        mem[0x0001] = value; // Immediate next value, which should be loaded to A

        // Execute Program

        cpu.Start( mem, 0x0000 ); 

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

    SECTION( "should run small script correctly with negative value" ) {
        
        // Immediate Byte to Load

        Byte value = 0xFF;

        // Assembly Program

        mem[0x0000] = INS_LDA_IM; // Sets the instruction at the PC
        mem[0x0001] = value; // Immediate next value, which should be loaded to A

        // Execute Program

        cpu.Start( mem, 0x0000 ); 

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

    SECTION( "should run small script correctly with positive value" ) {
        
        // Immediate Byte to Load

        Byte value = 0x65;

        // Assembly Program

        mem[0x0000] = INS_LDA_IM; // Sets the instruction at the PC
        mem[0x0001] = value; // Immediate next value, which should be loaded to A

        // Execute Program

        cpu.Start( mem, 0x0000 );

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









// LDA_ZP Test Case

TEST_CASE( "LDA Zero Page Instruction" ) {
    
    // Reset memory and PC each test

    cpu.Reset( mem );

    SECTION( "should have proper OP Code" ) {
        REQUIRE ( INS_LDA_ZP == 0xA5 );
    }

    SECTION( "should run script correctly with zero value" ) {
        
        // Byte to Load

        Byte value = 0x00;

        // Address of Byte

        Byte address = 0xFF;

        // Assembly Program

        mem[0x0000] = INS_LDA_ZP; // Sets the instruction at the PC
        mem[0x0001] = address; // Holds zero page address where value is contained
        mem[address] = value; // Script value, which should be loaded to A

        // Execute Program

        cpu.Start( mem, 0x0000 ); 

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

    SECTION( "should run small script correctly with negative value" ) {
        
        // Byte to Load

        Byte value = 0xFF;

        // Address of Byte

        Byte address = 0xFF;

        // Assembly Program

        mem[0x0000] = INS_LDA_ZP; // Sets the instruction at the PC
        mem[0x0001] = address; // Holds zero page address where value is contained
        mem[address] = value; // Script value, which should be loaded to A

        // Execute Program

        cpu.Start( mem, 0x0000 ); 

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

    SECTION( "should run small script correctly with positive value" ) {
        
        // Immediate Byte to Load

        Byte value = 0x65;

        // Address of Byte

        Byte address = 0xFF;

        // Assembly Program

        mem[0x0000] = INS_LDA_ZP; // Sets the instruction at the PC
        mem[0x0001] = address; // Holds zero page address where value is contained
        mem[address] = value; // Script value, which should be loaded to A

        // Execute Program

        cpu.Start( mem, 0x0000 );

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