#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PLP Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();
    Byte S = random<Byte>(1, 255);

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.S = S;

    // Set memory locations based on section parameters

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x28;

    };

    mem[PC] = OPCode;
    mem[S + 0x0100 - 1] = value;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.S == S - 1);
    
    REQUIRE(cpu.N == (value & 0b10000000) >> 7);
    REQUIRE(cpu.V == (value & 0b01000000) >> 6);
    REQUIRE(cpu.B == (value & 0b00010000) >> 4);
    REQUIRE(cpu.D == (value & 0b00001000) >> 3);
    REQUIRE(cpu.I == (value & 0b00000100) >> 2);
    REQUIRE(cpu.Z == (value & 0b00000010) >> 1);
    REQUIRE(cpu.C == (value & 0b00000001));

}