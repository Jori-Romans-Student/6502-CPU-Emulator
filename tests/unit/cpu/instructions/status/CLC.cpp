#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CLC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x18
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CLC);
        }
    };

    SECTION("executes correctly on cleared flag") {
        
        cpu.C = 0;

        cpu.Execute(CLC, 0x00);

        REQUIRE(cpu.C == 0);
    };

    SECTION("executes correctly on set flag") {
        
        cpu.C = 1;

        cpu.Execute(CLC, 0x00);

        REQUIRE(cpu.C == 0);
    };
}