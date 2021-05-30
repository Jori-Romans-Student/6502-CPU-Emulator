#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PHA Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte A = random<Byte>();
    Byte S = random<Byte>(0, 254);

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.A = A;
    cpu.S = S;

    // Set memory locations based on section parameters

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x48;

    };

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.S == S + 1);
    REQUIRE(mem[S + 0x0100] == A);

}