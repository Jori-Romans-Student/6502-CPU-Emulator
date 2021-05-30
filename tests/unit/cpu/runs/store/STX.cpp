#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("STX Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte X = random<Byte>();

    // Local Vars

    Word address;
    Byte OPCode;
    Byte Y;

    // Configure CPU

    cpu.PC = PC;
    cpu.X = X;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x8E;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0x86;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPY addressing mode test config") {

        // Config

        OPCode = 0x96;
        address = random<Byte>();
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(mem[address] == X);

}