#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ROR instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x6A, 0x66, 0x76, 0x6E, 0x7E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ROR);
        }
    };
}