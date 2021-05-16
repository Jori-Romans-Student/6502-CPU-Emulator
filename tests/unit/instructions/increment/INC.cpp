#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("INC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[4] = { 
            0xE6, 0xF6, 0xEE, 0xFE
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == INC);
        }
    };
}