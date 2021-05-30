#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ADC Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();
    Byte A = random<Byte>();
    Bit C = random<Bit>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte sum;
    Byte OPCode;
    Byte X;
    Byte Y;

    // Configure CPU

    cpu.A = A;
    cpu.C = C;
    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x6D;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0x7D;
        address = random<Word>(0x5000, 0x7FFF);
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - X) >> 8;
        mem[PC + 2] = address - X;

        // Config Register

        cpu.X = X;

    };

    SECTION("ABY addressing mode test config") {

        // Config

        OPCode = 0x79;
        address = random<Word>(0x5000, 0x7FFF);
        Y = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - Y) >> 8;
        mem[PC + 2] = address - Y;

        // Config Register

        cpu.Y = Y;

    };

    SECTION("IMM addressing mode test config") {

        // Config

        OPCode = 0x69;
        address = PC + 1;

    };

    SECTION("IDX addressing mode test config") {

        // Config

        OPCode = 0x61;
        addressOfAddress = random<Byte>();
        address = random<Word>(0x5000, 0x7FFF);
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

        OPCode = 0x71;
        addressOfAddress = random<Byte>();
        address = random<Word>(0x5000, 0x7FFF);
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

        OPCode = 0x65;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0x75;
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

    sum = A + value + C;

    // Assertions

    REQUIRE(cpu.A == sum);
    REQUIRE(cpu.C == isAddedOverflow(A, value + C));
    REQUIRE(cpu.V == isAddedOverflow(A, value + C));
    REQUIRE(cpu.N == isNegative(sum));
    REQUIRE(cpu.Z == isZero(sum));

}