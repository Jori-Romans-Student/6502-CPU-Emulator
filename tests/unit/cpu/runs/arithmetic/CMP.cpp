#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CMP Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();
    Byte A = random<Byte>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte OPCode;
    Byte difference;
    Byte X;
    Byte Y;

    // Configure CPU

    cpu.A = A;
    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0xCD;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0xDD;
        address = random<Word>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - X) >> 8;
        mem[PC + 2] = address - X;

        // Config Register

        cpu.X = X;

    };

    SECTION("ABY addressing mode test config") {

        // Config

        OPCode = 0xD9;
        address = random<Word>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - Y) >> 8;
        mem[PC + 2] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    SECTION("IMM addressing mode test config") {

        // Config

        OPCode = 0xC9;
        address = PC + 1;

    };

    SECTION("IDX addressing mode test config") {

        // Config

        OPCode = 0xC1;
        addressOfAddress = random<Byte>();
        address = random<Word>();
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = addressOfAddress;
        mem[addressOfAddress + X] = address >> 8;
        mem[addressOfAddress + X + 1] = address;

        // Config Register

        cpu.X = X;

    };

    SECTION("IDY addressing mode test config") {

        // Config

        OPCode = 0xD1;
        addressOfAddress = random<Byte>();
        address = random<Word>();
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = addressOfAddress;
        mem[addressOfAddress] = (address - Y) >> 8;
        mem[addressOfAddress + 1] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0xC5;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0xD5;
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

    // Difference

    difference = A - value;

    // Assertions

    REQUIRE(cpu.C == (A >= value));
    REQUIRE(cpu.N == isNegative(difference));
    REQUIRE(cpu.Z == isZero(difference));

}