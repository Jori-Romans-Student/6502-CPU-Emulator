#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Absolute Y addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte Y;
    Word PC;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[9] = { 
            0xB9, 0xBE, 0x79, 0x39, 0xD9,
            0x59, 0x19, 0xF9, 0x99
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ABY);
        }
    };

    SECTION("returns proper address for random PC and Y register") {

        PC = (Word) rand();
        Y = (Byte) rand();
        address = (Word) rand();

        cpu.PC = PC;
        cpu.Y = Y;

        mem[PC] = (Byte) (address >> 8);
        mem[PC + 1] = (Byte) address;

        REQUIRE(cpu.Address(ABY) == address + Y);
    };
}