#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PHP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte N;
    Byte V;
    Byte B;
    Byte D;
    Byte I;
    Byte Z;
    Byte C;

    Byte received;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x08
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == PHP);
        }
    };

    SECTION("executes properly on random P value") {
        
        N = rand() % 2;
        V = rand() % 2;
        B = rand() % 2;
        D = rand() % 2;
        I = rand() % 2;
        Z = rand() % 2;
        C = rand() % 2;

        cpu.N = N;
        cpu.V = V;
        cpu.B = B;
        cpu.D = D;
        cpu.I = I;
        cpu.Z = Z;
        cpu.C = C;
        
        cpu.Execute(PHP, 0);

        received = mem[0x0100];

        REQUIRE(cpu.S == 0x01);

        REQUIRE((received & 0b10000000) >> 7 == N);
        REQUIRE((received & 0b01000000) >> 6 == V);
        REQUIRE((received & 0b00010000) >> 4 == B);
        REQUIRE((received & 0b00001000) >> 3 == D);
        REQUIRE((received & 0b00000100) >> 2 == I);
        REQUIRE((received & 0b00000010) >> 1 == Z);
        REQUIRE((received & 0b00000001) == C);
    };
}