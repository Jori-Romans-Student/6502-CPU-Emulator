#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("INC Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();

    // Local Vars

    Word address;
    Byte sum;
    Byte OPCode;
    Byte X;

    // Configure CPU

    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0xEE;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0xFE;
        address = random<Word>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - X) >> 8;
        mem[PC + 2] = address - X;

        // Config Register

        cpu.X = X;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0xE6;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0xF6;
        address = random<Byte>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address - X;

        // Config Register

        cpu.X = X;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Sum

    sum = value + 1;

    // Assertions

    REQUIRE(mem[address] == sum);
    REQUIRE(cpu.N == isNegative(sum));
    REQUIRE(cpu.Z == isZero(sum));

}