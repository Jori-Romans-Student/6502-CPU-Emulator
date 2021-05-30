#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("RTS instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Word PC;
    Byte S;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x60
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == RTS);
        }
    };

    SECTION("executes correctly on random address") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        address = random<Word>(0x5000, 0x7FFF);
        S = 0x02;

        cpu.PC = PC;
        cpu.S = S;

        mem[0x0100] = (Byte) (address >> 8);
        mem[0x0101] = (Byte) address;

        cpu.Execute(RTS, 0x00);

        REQUIRE(cpu.PC == address);
        REQUIRE(cpu.S == 0x00);
    };
}