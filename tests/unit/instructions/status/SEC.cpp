#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("SEC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x38
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == SEC);
        }
    };

    SECTION("executes correctly on cleared flag") {
        
        C = 0;
        cpu.C = C;

        cpu.Execute(SEC, 0x00);

        REQUIRE(cpu.C == 1);
    };

    SECTION("executes correctly on set flag") {
        
        C = 1;
        cpu.C = C;

        cpu.Execute(SEC, 0x00);

        REQUIRE(cpu.C == 1);
    };
}