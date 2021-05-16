#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ORA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x09, 0x05, 0x15, 0x0D, 0x1D,
            0x19, 0x01, 0x11
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ORA);
        }
    };
}