#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CLD instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xD8
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CLD);
        }
    };

    SECTION("executes correctly on cleared flag") {
        
        cpu.D = 0;

        cpu.Execute(CLD, 0x00);

        REQUIRE(cpu.D == 0);
    };

    SECTION("executes correctly on set flag") {
        
        cpu.D = 1;

        cpu.Execute(CLD, 0x00);

        REQUIRE(cpu.D == 0);
    };
}