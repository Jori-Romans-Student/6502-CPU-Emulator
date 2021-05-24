#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Absolute addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word PC;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[23] = { 
            0xAD, 0xAE, 0xAC, 0x6D, 0x2D,
            0x0E, 0x2C, 0xCD, 0xEC, 0xCC,
            0xCE, 0x4D, 0xEE, 0x4C, 0x20,
            0x4E, 0x0D, 0x2E, 0x6E, 0xED,
            0x8D, 0x8E, 0x8C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == AB);
        }
    };

    SECTION("returns proper address for random PC") {

        PC = random<Word>();
        address = random<Word>();
        cpu.PC = PC;

        mem[PC] = (Byte) (address >> 8);
        mem[PC + 1] = (Byte) address;

        REQUIRE(cpu.Address(AB) == address);
    };
}