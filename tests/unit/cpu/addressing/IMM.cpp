#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Immediate addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Word address;
    Location expected;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[11] = { 
            0xA9, 0xA2, 0xA0, 0x69, 0x29,
            0xC9, 0xE0, 0xC0, 0x49, 0x09,
            0xE9
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IMM);
        }
    };

    SECTION("returns proper address for random PC") {

        PC = random<Word>(0x1000, 0x3FFF);
        expected = Location(PC);

        cpu.PC = PC;

        REQUIRE(cpu.Locate(IMM) == expected);
        REQUIRE(cpu.PC == PC + 1);
    };
}