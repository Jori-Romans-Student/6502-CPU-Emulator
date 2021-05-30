#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("TYA Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte Y = random<Byte>();

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.Y = Y;

    // Set memory locations based on section parameters

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x98;

    };

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.A == Y);
    REQUIRE(cpu.N == isNegative(Y));
    REQUIRE(cpu.Z == isZero(Y));

}