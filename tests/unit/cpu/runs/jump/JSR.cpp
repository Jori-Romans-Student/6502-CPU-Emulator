#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("JSR Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte S = random<Byte>(0, 253);

    // Local Vars

    Word address;
    Byte OPCode;
    Word returnAddress;

    // Configure CPU

    cpu.PC = PC;
    cpu.S = S;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x20;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Return address

    returnAddress = (Word) (mem[S + 256] << 8 | mem[S + 257]);

    // Assertions

    REQUIRE(cpu.PC == address);
    REQUIRE(cpu.S == S + 2);
    REQUIRE(returnAddress == (PC + 3) - 1);

}