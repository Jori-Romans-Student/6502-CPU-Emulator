#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("EOR instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x49, 0x45, 0x55, 0x4D, 0x5D,
            0x59, 0x41, 0x51
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == EOR);
        }
    };
}