#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("JMP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Word PC;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[2] = { 
            0x4C, 0x6C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == JMP);
        }
    };

    SECTION("executes correctly on random address") {
        
        PC = (Word) rand();
        address = (Word) rand();

        cpu.PC = PC;

        cpu.Execute(JMP, address);

        REQUIRE(cpu.PC == address);
    }
}