#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PLA Run Tests") {

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

        OPCode = 0x68;

    };

    mem[PC] = OPCode;
    mem[S + 0x0100 - 1] = value;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.S == S - 1);
    REQUIRE(cpu.A == value);
    REQUIRE(cpu.Z == isZero(value));
    REQUIRE(cpu.N == isNegative(value));

}