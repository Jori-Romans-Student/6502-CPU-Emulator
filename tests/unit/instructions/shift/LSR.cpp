#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LSR instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x4A, 0x46, 0x56, 0x4E, 0x5E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == LSR);
        }
    };
}