#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CPY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[3] = { 
            0xC0, 0xC4, 0xCC
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CPY);
        }
    };
}