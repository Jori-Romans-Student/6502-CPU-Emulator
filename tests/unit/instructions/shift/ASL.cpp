#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ASL instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x0A, 0x06, 0x16, 0x0E, 0x1E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ASL);
        }
    };
}