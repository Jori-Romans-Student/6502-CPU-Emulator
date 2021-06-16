#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("RTI Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Word newPC = random<Word>(0x1000, 0x3FFF);
    Byte S = random<Byte>(3, 255);
    Byte P = random<Byte>();

    // Local Vars

    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.S = S;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x40;

        mem[0xFD + S] = (Byte) (newPC >> 8);
        mem[0xFE + S] = (Byte) newPC;
        mem[0xFF + S] = (Byte) P;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.PC == newPC);
    REQUIRE(cpu.S == S - 3);

    REQUIRE(cpu.N == (P & 0x80) > 0);
    REQUIRE(cpu.V == (P & 0x40) > 0);
    REQUIRE(cpu.B == (P & 0x10) > 0);
    REQUIRE(cpu.D == (P & 0x08) > 0);
    REQUIRE(cpu.I == (P & 0x04) > 0);
    REQUIRE(cpu.Z == (P & 0x02) > 0);
    REQUIRE(cpu.C == (P & 0x01) > 0);
}