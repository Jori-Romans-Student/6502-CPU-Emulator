#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Indirect X addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    // Word PC;
    // Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xA1, 0x61, 0x21, 0xC1, 0x41,
            0x01, 0xE1, 0x81
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IDX);
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