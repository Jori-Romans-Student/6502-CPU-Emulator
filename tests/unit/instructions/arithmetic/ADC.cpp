#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ADC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x69, 0x65, 0x75, 0x6D, 0x7D, 
            0x79, 0x61, 0x71
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ADC);
        }
    };
}