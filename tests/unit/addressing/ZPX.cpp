#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Zero Page X addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte X;
    Word PC;
    Byte address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[16] = { 
            0xB5, 0xB4, 0x75, 0x35, 0x16,
            0xD5, 0xD6, 0x55, 0xF6, 0x56,
            0x15, 0x36, 0x76, 0xF5, 0x95,
            0x94
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ZPX);
        }
    };

    SECTION("returns proper address for random PC and X Register") {

        PC = (Word) rand();
        X = (Byte) rand();
        address = (Byte) rand();

        cpu.PC = PC;
        cpu.X = X;

        mem[PC] = (Byte) (address);

        REQUIRE(cpu.Address(ZPX) == address + X);
    };
}