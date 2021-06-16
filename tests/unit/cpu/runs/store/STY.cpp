#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("STY Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte Y = random<Byte>();

    // Local Vars

    Word address;
    Byte OPCode;
    Byte X;

    // Configure CPU

    cpu.PC = PC;
    cpu.Y = Y;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x8C;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0x84;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0x94;
        address = random<Byte>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address - X;

        // Config Register

        cpu.X = X;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(mem[address] == Y);

}