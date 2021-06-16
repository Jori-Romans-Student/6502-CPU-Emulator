#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Accumulator addressing mode") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word PC;
    Word address;
    Location expected;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[2] = { 
            0x2A, 0x6A
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == AC);
        }
    };

    SECTION("returns null address for random PC") {

        expected = Location();

        REQUIRE(cpu.Locate(AC) == expected);
    };
}