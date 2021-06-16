#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("RTS Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte S = random<Byte>(2, 255);

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;
    cpu.S = S;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0x60;
        address = random<Word>(0x5000, 0x7FFF);

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[S - 2 + 0x0100] = (Byte) (address >> 8);
    mem[S - 1 + 0x0100] = (Byte) address;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.PC == address);
    REQUIRE(cpu.S == S - 2);

}