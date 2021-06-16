#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Indirect Y addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte Y;
    Word PC;
    Byte addressOfAddress;
    Word address;
    Location expected;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xB1, 0x71, 0x31, 0xD1, 0x51,
            0x11, 0xF1, 0x91
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IDY);
        }
    };

    SECTION("returns proper address for random PC and Y Register") {

        PC = random<Word>(0x1000, 0x3FFF);
        Y = random<Byte>();
        addressOfAddress = random<Byte>();
        address = random<Word>(0x5000, 0x7FFF);
        expected = Location(address + Y);
        
        cpu.PC = PC;
        cpu.Y = Y;

        mem[PC] = (Byte) (addressOfAddress);
        mem[addressOfAddress] = (Byte) (address >> 8);
        mem[addressOfAddress + 1] = (Byte) address;

        REQUIRE(cpu.Locate(IDY) == expected);
    };
}