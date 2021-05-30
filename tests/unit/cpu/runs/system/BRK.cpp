#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BRK Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Word value = random<Byte>();
    Byte S = random<Byte>(0, 252);

    Bit N = random<Bit>();
    Bit V = random<Bit>();
    Bit B = random<Bit>();
    Bit D = random<Bit>();
    Bit I = random<Bit>();
    Bit Z = random<Bit>();
    Bit C = random<Bit>();

    // Local Vars

    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.S = S;

    cpu.N = N;
    cpu.V = V;
    cpu.B = B;
    cpu.D = D;
    cpu.I = I;
    cpu.Z = Z;
    cpu.C = C;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x00;

        mem[0xFFFE] = (Byte) (value >> 8);
        mem[0xFFFF] = (Byte) (value);

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.PC == value);
    REQUIRE(cpu.S == S + 3);

    REQUIRE(PC + 1 == (mem[S + 0x0100] << 8 | mem[S + 0x0101]));
    REQUIRE(mem[S + 0x0102] == ((N << 7) | (V << 6) | (B << 4) | (D << 3) | (I << 2) | (Z << 1) | C));

    REQUIRE(cpu.B == 1);
}