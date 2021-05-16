#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ROL instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x2A, 0x26, 0x36, 0x2E, 0x3E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ROL);
        }
    };
}