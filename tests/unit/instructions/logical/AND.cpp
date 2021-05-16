#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("AND instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x29, 0x25, 0x35, 0x2D, 0x3D,
            0x39, 0x21, 0x31
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == AND);
        }
    };
}