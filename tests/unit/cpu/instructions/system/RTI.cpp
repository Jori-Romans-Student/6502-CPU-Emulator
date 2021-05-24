#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("RTI instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Word newPC;
    Byte S;
    Byte SP;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x40
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == RTI);
        }
    };

    SECTION("executes correctly on random PC and processor status") {
        
        PC = random<Word>();
        newPC = random<Word>();
        S = 0x03;
        SP = random<Byte>();

        cpu.PC = PC;
        cpu.S = S;

        mem[0x0100] = (Byte) (newPC >> 8);
        mem[0x0101] = (Byte) newPC;
        mem[0x0102] = (Byte) SP;

        cpu.Execute(RTI, 0x00);

        REQUIRE(cpu.PC == newPC);
        REQUIRE(cpu.S == S - 3);

        REQUIRE(cpu.N == (SP & 0x80) > 0);
        REQUIRE(cpu.V == (SP & 0x40) > 0);
        REQUIRE(cpu.B == (SP & 0x10) > 0);
        REQUIRE(cpu.D == (SP & 0x08) > 0);
        REQUIRE(cpu.I == (SP & 0x04) > 0);
        REQUIRE(cpu.Z == (SP & 0x02) > 0);
        REQUIRE(cpu.C == (SP & 0x01) > 0);

    };
}