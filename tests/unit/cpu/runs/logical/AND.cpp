#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("AND Run Tests") {

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
    Byte product;
    Byte OPCode;
    Byte X;
    Byte Y;

    // Configure CPU

    cpu.A = A;
    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x2D;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0x3D;
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

        OPCode = 0x39;
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

        OPCode = 0x29;
        address = PC + 1;

    };

    SECTION("IDX addressing mode test config") {

        // Config

        OPCode = 0x21;
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

        OPCode = 0x31;
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

        OPCode = 0x25;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0x35;
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

    product = value & A;

    // Assertions

    REQUIRE(cpu.A == product);
    REQUIRE(cpu.Z == isZero(product));
    REQUIRE(cpu.N == isNegative(product));

}