#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CPY Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();
    Byte Y = random<Byte>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte OPCode;
    Byte difference;

    // Configure CPU

    cpu.Y = Y;
    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0xCC;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("IMM addressing mode test config") {

        // Config

        OPCode = 0xC0;
        address = PC + 1;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0xC4;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Difference

    difference = Y - value;

    // Assertions

    REQUIRE(cpu.C == (Y >= value));
    REQUIRE(cpu.N == isNegative(difference));
    REQUIRE(cpu.Z == isZero(difference));

}