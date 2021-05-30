#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Zero Page Y addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
 
    Byte Y;
    Word PC;
    Byte address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[2] = { 
            0xB6, 0x96
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ZPY);
        }
    };

    SECTION("returns proper address for random PC and Y Register") {

        PC = random<Word>(0x1000, 0x3FFF);
        Y = random<Byte>();
        address = random<Byte>();

        cpu.PC = PC;
        cpu.Y = Y;

        mem[PC] = (Byte) (address);

        REQUIRE(cpu.Address(ZPY) == (Byte) (address + Y));
    };
}