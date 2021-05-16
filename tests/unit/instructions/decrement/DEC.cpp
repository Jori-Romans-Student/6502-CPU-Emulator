#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("DEC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[4] = { 
            0xC6, 0xD6, 0xCE, 0xDE
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == DEC);
        }
    };
}