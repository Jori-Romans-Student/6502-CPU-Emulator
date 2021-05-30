#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("NOP Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);

    // Local Vars

    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0xEA;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.PC == PC + 1);
}