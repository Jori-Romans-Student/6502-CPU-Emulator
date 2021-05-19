#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CPX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Byte X;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[3] = { 
            0xE0, 0xE4, 0xEC
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CPX);
        }
    };

    SECTION("executes properly when equal") {

        address = (Word) rand();
        value = (Byte) rand();
        X = value;

        cpu.X = X;

        mem[address] = value;

        cpu.Execute(CPX, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 1);
    };

    SECTION("executes properly when less then and negative") {

        address = (Word) rand();
        value = (Byte) rand();
        X = value - 1;

        cpu.X = X;

        mem[address] = value;

        cpu.Execute(CPX, address);

        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when less then and positive") {

        address = (Word) rand();
        value = (Byte) rand() | 0x81;
        X = value - 129;

        cpu.X = X;

        mem[address] = value;

        cpu.Execute(CPX, address);

        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when greater then and negative") {

        address = (Word) rand();
        value = (Byte) rand() & 0x7F;
        X = value + 128;

        cpu.X = X;

        mem[address] = value;

        cpu.Execute(CPX, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when greater then and postive") {

        address = (Word) rand();
        value = (Byte) rand();
        X = value + 1;

        cpu.X = X;

        mem[address] = value;

        cpu.Execute(CPX, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };
}