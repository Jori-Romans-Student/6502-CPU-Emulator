#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("STA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word PC;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[7] = { 
            0x85, 0x95, 0x8D, 0x9D, 0x99,
            0x81, 0x91
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == STA);
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