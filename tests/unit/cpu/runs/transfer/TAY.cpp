#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("TAY Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte A = random<Byte>();

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.A = A;

    // Set memory locations based on section parameters

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0xA8;

    };

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.Y == A);
    REQUIRE(cpu.N == isNegative(A));
    REQUIRE(cpu.Z == isZero(A));

}