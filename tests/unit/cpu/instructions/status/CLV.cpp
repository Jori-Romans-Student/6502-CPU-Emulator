#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CLV instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xB8
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CLV);
        }
    };

    SECTION("executes correctly on cleared flag") {
        
        cpu.V = 0;

        cpu.Execute(CLV, 0x00);

        REQUIRE(cpu.V == 0);
    };

    SECTION("executes correctly on set flag") {
        
        cpu.V = 1;

        cpu.Execute(CLV, 0x00);

        REQUIRE(cpu.V == 0);
    };
}