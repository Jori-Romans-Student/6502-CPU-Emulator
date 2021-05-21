#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PLP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte P;
    Byte address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x28
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == PLP);
        }
    };

    SECTION("executes properly on random value") {
        P = (Byte) rand();
        mem[0x0100] = P;
        cpu.S += 1;

        cpu.Execute(PLP, 0);

        REQUIRE(cpu.S == 0x00);

        REQUIRE(cpu.N == (P & 0b10000000) >> 7);
        REQUIRE(cpu.V == (P & 0b01000000) >> 6);
        REQUIRE(cpu.B == (P & 0b00010000) >> 4);
        REQUIRE(cpu.D == (P & 0b00001000) >> 3);
        REQUIRE(cpu.I == (P & 0b00000100) >> 2);
        REQUIRE(cpu.Z == (P & 0b00000010) >> 1);
        REQUIRE(cpu.C == (P & 0b00000001));
        
    };
}