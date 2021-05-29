#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("DEX Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();

    // Local Vars

    Word address;
    Byte difference;
    Byte OPCode;
    Byte X;

    // Configure CPU

    cpu.PC = PC;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0xCA;
        X = value;
        cpu.X = X;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Sum

    difference = value - 1;

    // Assertions

    REQUIRE(cpu.X == difference);
    REQUIRE(cpu.N == isNegative(difference));
    REQUIRE(cpu.Z == isZero(difference));

}