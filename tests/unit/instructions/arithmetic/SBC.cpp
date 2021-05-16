#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("SBC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xE9, 0xE5, 0xF5, 0xED, 0xFD,
            0xF9, 0xE1, 0xF1
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == SBC);
        }
    };
}