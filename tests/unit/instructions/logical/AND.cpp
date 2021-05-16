#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("AND instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte A;
    Byte value;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x29, 0x25, 0x35, 0x2D, 0x3D,
            0x39, 0x21, 0x31
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == AND);
        }
    };

    SECTION("executes properly on zero value") {

        value = (Byte) 0x00;
        address = (Word) rand();
        A = (Byte) rand();
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(AND, address);

        REQUIRE(cpu.A == (value & A));
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        value = (Byte) 0x75;
        address = (Word) rand();
        A = (Byte) rand() | 0x01; // gurantees not zero
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(AND, address);

        REQUIRE(cpu.A == (value & A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        value = (Byte) 0xA9;
        address = (Word) rand();
        A = (Byte) rand() | 0x80; // gurantees negative
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(AND, address);

        REQUIRE(cpu.A == (value & A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}