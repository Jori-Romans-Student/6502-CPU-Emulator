#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Relative addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    // Word PC;
    // Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x10, 0x30, 0x50, 0x70, 0x90,
            0xB0, 0xD0, 0xF0
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == REL);
        }
    };

    // SECTION("returns proper address for random PC") {

    //     PC = (Word) rand();
    //     address = (Word) rand();
    //     cpu.PC = PC;

    //     mem[PC] = (Byte) (address >> 8);
    //     mem[PC + 1] = (Byte) address;

    //     REQUIRE(cpu.Address(AB) == address);
    // };
}