#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("SBC Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();
    Byte A = random<Byte>();
    Bit C = random<Bit>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte difference;
    Byte OPCode;
    Byte X;
    Byte Y;

    // Configure CPU

    cpu.A = A;
    cpu.C = C;
    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0xED;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0xFD;
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

        OPCode = 0xF9;
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

        OPCode = 0xE9;
        address = PC + 1;

    };

    SECTION("IDX addressing mode test config") {

        // Config

        OPCode = 0xE1;
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

        OPCode = 0xF1;
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

        OPCode = 0xE5;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0xF5;
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

    difference = A - (value + !C);

    // Assertions

    REQUIRE(cpu.A == difference);
    REQUIRE(cpu.C == !isSubtractedOverflow(A, value + !C));
    REQUIRE(cpu.V == isSubtractedOverflow(A, value + !C));
    REQUIRE(cpu.N == isNegative(difference));
    REQUIRE(cpu.Z == isZero(difference));

}