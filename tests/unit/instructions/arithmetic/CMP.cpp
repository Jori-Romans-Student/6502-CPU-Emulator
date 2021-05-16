#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CMP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xC9, 0xC5, 0xD5, 0xCD, 0xDD, 
            0xD9, 0xC1, 0xD1
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CMP);
        }
    };
}