#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("LDX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word PC;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0xA2, 0xA6, 0xB6, 0xAE, 0xBE 
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == LDX);
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