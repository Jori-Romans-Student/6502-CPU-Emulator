#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("TSX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte value;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xBA
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TSX);
        }
    };

    SECTION("executes properly on zero value") {

        address = 0x0100;
        value = (Byte) 0x00;

        mem[address] = value;
        cpu.S += 1;

        cpu.Execute(TSX, 0);

        REQUIRE(cpu.X == value);
        REQUIRE(cpu.S == (Byte) address);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = 0x0100;
        value = (Byte) 0x6B;

        mem[address] = value;
        cpu.S += 1;

        cpu.Execute(TSX, 0);

        REQUIRE(cpu.X == value);
        REQUIRE(cpu.S == (Byte) address);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = 0x0100;
        value = (Byte) 0xAC;

        mem[address] = value;
        cpu.S += 1;

        cpu.Execute(TSX, 0);

        REQUIRE(cpu.X == value);
        REQUIRE(cpu.S == (Byte) address);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}