#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Indirect addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Word PC;
    Word address;
    Word addressOfAddress;
    Location expected;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x6C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ID);
        }
    };

    SECTION("returns proper address for random PC and address") {

        PC = random<Word>(0x1000, 0x3FFF);
        addressOfAddress = random<Word>(0x9000, 0xBFFF);
        address = random<Word>(0x5000, 0x7FFF);
        expected = Location(address);
        
        cpu.PC = PC;

        mem[PC] = (Byte) (addressOfAddress >> 8);
        mem[PC + 1] = (Byte) (addressOfAddress);
        mem[addressOfAddress] = (Byte) (address >> 8);
        mem[addressOfAddress + 1] = (Byte) address;

        REQUIRE(cpu.Locate(ID) == expected);
    };
}