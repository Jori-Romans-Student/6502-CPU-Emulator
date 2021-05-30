#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("NOP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xEA
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == NOP);
        }
    };

    SECTION("executes properly on random PC") {
        
        PC = random<Word>();

        cpu.PC = PC;

        cpu.Execute(NOP, 0x00);

        REQUIRE(cpu.PC == PC);
    }
}