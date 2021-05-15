#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LDA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xA9, 0xA5, 0xB5, 0xAD, 0xBD, 
            0xB9, 0xA1, 0xB1 
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == LDA);
        }
    };

    SECTION("executes properly on zero value") {

        address = (Word) rand();
        value = (Byte) 0x00;

        mem[address] = value;

        cpu.Execute(LDA, address);

        REQUIRE(cpu.A == value);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = (Word) rand();
        value = (Byte) 0x27;

        mem[address] = value;

        cpu.Execute(LDA, address);

        REQUIRE(cpu.A == value);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = (Word) rand();
        value = (Byte) 0xA6;

        mem[address] = value;

        cpu.Execute(LDA, address);

        REQUIRE(cpu.A == value);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}