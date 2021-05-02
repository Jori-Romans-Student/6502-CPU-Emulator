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

    SECTION( "should run script correctly with all negative values" ) {
        
        // Amount of runs for negative values

        int runs = 128;

        // First negative value

        Byte value = 0x80;

        while (runs > 0) {
            
            // Reset CPU

            cpu.Reset( mem );

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

            // Decrement amount of runs

            runs--;

            // Increment value

            value++;
        }
    }

    SECTION( "should run script correctly with all positive values" ) {
        
        // Amount of runs for negative values

        int runs = 127;

        // First negative value

        Byte value = 0x01;

        while (runs > 0) {
            
            // Reset CPU

            cpu.Reset( mem );

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

            // Decrement amount of runs

            runs--;

            // Increment value

            value++;
        }
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

        Byte address = 0x02;

        // Amount of runs for zero addresses

        int runs = 254;

        while (runs > 0) {

            // Reset CPU

            cpu.Reset( mem );

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

            // Increment Address Used

            address++;

            // Decrement Runs

            runs--;
        }
    }

    SECTION( "should run script correctly with negative values" ) {
        
        // Byte to Load

        Byte value = 0x80;

        // Address of Byte

        Byte address = 0x02;

        // Amount of runs for zero addresses

        int address_runs = 254;

        // Loop over every zero address;

        while (address_runs > 0) {

            // Amount of run for values

            int value_runs = 128;

            // Loop over every negative value

            while (value_runs > 0) {

                // Reset CPU

                cpu.Reset( mem );
                
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

                REQUIRE( cpu.Z == 0);

                // Run Assertion on Negative Flag

                REQUIRE( cpu.N == 1 );

                // Run Assertion on A Register to ensure proper load

                REQUIRE( cpu.A == value );

                // Increment Value

                value++;

                // Decrement Value Runs

                value_runs--;
            }

            // Reset Value

            value = 0x80;  

            // Increment Address Used

            address++;

            // Decrement Address Runs

            address_runs--;
        }
    }

    SECTION( "should run script correctly with positive values" ) {
        
        // Byte to Load

        Byte value = 0x01;

        // Address of Byte

        Byte address = 0x02;

        // Amount of runs for zero addresses

        int address_runs = 254;

        // Loop over every zero address;

        while (address_runs > 0) {

            // Amount of run for values

            int value_runs = 127;

            // Loop over every negative value

            while (value_runs > 0) {

                // Reset CPU

                cpu.Reset( mem );
                
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

                REQUIRE( cpu.Z == 0);

                // Run Assertion on Negative Flag

                REQUIRE( cpu.N == 0 );

                // Run Assertion on A Register to ensure proper load

                REQUIRE( cpu.A == value );

                // Increment Value

                value++;

                // Decrement Value Runs

                value_runs--;
            }

            // Reset Value

            value = 0x01;  

            // Increment Address Used

            address++;

            // Decrement Address Runs

            address_runs--;
        }
    }

    SECTION( "should run script incorrectly" ) {
        
        // Byte to Load

        Byte value = 0x01;

        // Address of Byte

        Byte address = 0x02;

        // Amount of runs for zero addresses

        int address_runs = 254;

        // Loop over every zero address;

        while (address_runs > 0) {

            // Amount of run for values

            int value_runs = 127;

            // Loop over every negative value

            while (value_runs > 0) {

                // Reset CPU

                cpu.Reset( mem );
                
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

                REQUIRE( cpu.Z == 0);

                // Run Assertion on Negative Flag

                REQUIRE( cpu.N == 0 );

                // Run Assertion on A Register to ensure proper load

                REQUIRE( cpu.A == value );

                // Increment Value

                value++;

                // Decrement Value Runs

                value_runs--;
            }

            // Reset Value

            value = 0x01;  

            // Increment Address Used

            address++;

            // Decrement Address Runs

            address_runs--;
        }
    }
}