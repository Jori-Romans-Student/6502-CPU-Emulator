#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Absolute X addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    // Word PC;
    // Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[15] = { 
            0xBD, 0xBC, 0x7D, 0x3D, 0x1E,
            0xDD, 0xDE, 0x5D, 0xFE, 0x5E,
            0x1D, 0x3E, 0x7E, 0xFD, 0x9D
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ABX);
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