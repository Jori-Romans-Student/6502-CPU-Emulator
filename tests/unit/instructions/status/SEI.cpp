#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("SEI instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x78
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == SEI);
        }
    };

    SECTION("executes correctly on cleared flag") {
        
        cpu.I = 0;

        cpu.Execute(SEI, 0x00);

        REQUIRE(cpu.I == 1);
    };

    SECTION("executes correctly on set flag") {
    
        cpu.I = 1;

        cpu.Execute(SEI, 0x00);

        REQUIRE(cpu.I == 1);
    };
}