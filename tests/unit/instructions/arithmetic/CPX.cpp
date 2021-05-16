#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CPX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[3] = { 
            0xE0, 0xE4, 0xEC
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CPX);
        }
    };
}