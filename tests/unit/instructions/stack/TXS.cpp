#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("TXS instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte X;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x9A
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TXS);
        }
    };

    SECTION("executes properly on random value") {

        X = (Byte) rand();
        cpu.X = X;

        cpu.Execute(TXS, 0);

        REQUIRE(cpu.S == X);
    };
}