#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PHA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte A;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x48
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == PHA);
        }
    };

    SECTION("executes properly on random A value") {
        A = (Byte) rand();
        cpu.A = A;

        cpu.Execute(PHA, 0);

        REQUIRE(mem[0x0100] == A);
        REQUIRE(cpu.S == 0x01);
    };
}