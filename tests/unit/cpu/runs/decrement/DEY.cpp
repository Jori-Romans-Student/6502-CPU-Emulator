#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("DEY Run Tests") {

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
    Byte Y;

    // Configure CPU

    cpu.PC = PC;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x88;
        Y = value;
        cpu.Y = Y;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Sum

    difference = value - 1;

    // Assertions

    REQUIRE(cpu.Y == difference);
    REQUIRE(cpu.N == isNegative(difference));
    REQUIRE(cpu.Z == isZero(difference));

}