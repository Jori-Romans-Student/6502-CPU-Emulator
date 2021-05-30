#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("SEI Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.I = 0;

    // Set memory locations based on section parameters

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x78;

    };

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.I == 1);

}