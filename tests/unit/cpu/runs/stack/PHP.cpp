#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PHP Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte S = random<Byte>(0, 254);

    Bit N = random<Bit>();
    Bit V = random<Bit>();
    Bit B = random<Bit>();
    Bit D = random<Bit>();
    Bit I = random<Bit>();
    Bit Z = random<Bit>();
    Bit C = random<Bit>();

    // Local Vars

    Word address;
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

    // Set memory locations based on section parameters

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x08;

    };

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.S == S + 1);
    REQUIRE(mem[S + 0x0100] == ((N << 7) | (V << 6) | (B << 4) | (D << 3) | (I << 2) | (Z << 1) | C));

}