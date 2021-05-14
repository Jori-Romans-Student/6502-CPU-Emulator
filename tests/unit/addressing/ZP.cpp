#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Zero Page addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[21] = { 
            0xA5, 0xA6, 0xA4, 0x65, 0x25,
            0x06, 0x24, 0xC5, 0xE4, 0xC4,
            0xC6, 0x45, 0xE6, 0x46, 0x05,
            0x26, 0x66, 0xE5, 0x85, 0x86, 
            0x84
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ZP);
        }
    };

    SECTION("returns proper address for random PC") {

        PC = (Word) rand();
        address = (Byte) rand();
        cpu.PC = PC;

        mem[PC] = (Byte) (address);

        REQUIRE(cpu.Address(ZP) == address);
    };
}