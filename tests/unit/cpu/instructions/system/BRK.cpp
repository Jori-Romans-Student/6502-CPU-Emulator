#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BRK instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte S;
    Word value;

    Bit N;
    Bit V;
    Bit B;
    Bit D;
    Bit I;
    Bit Z;
    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x00 
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BRK);
        }
    };

    SECTION("executes correctly on random PC and processor status") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        S = 0x00;
        value = random<Word>(); // replace later with proper interupt handler

        N = random<Bit>();
        V = random<Bit>();
        B = random<Bit>();
        D = random<Bit>();
        I = random<Bit>();
        Z = random<Bit>();
        C = random<Bit>();

        cpu.PC = PC;
        cpu.S = S;
        
        cpu.N = N;
        cpu.V = V;
        cpu.B = B;
        cpu.D = D;
        cpu.I = I;
        cpu.Z = Z;
        cpu.C = C;

        mem[0xFFFE] = (Byte) (value >> 8);
        mem[0xFFFF] = (Byte) (value);

        cpu.Execute(BRK, 0x00);

        REQUIRE(cpu.PC == value);
        REQUIRE(cpu.S == S + 3);

        REQUIRE((mem[0x0100] << 8 | mem[0x0101]) == PC);
        REQUIRE(mem[0x0102] == ((N << 7) | (V << 6) | (B << 4) | (D << 3) | (I << 2) | (Z << 1) | C));

        REQUIRE(cpu.B == 1);
    };
}