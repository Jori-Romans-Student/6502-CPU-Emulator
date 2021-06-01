#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ROL Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();
    Bit C = random<Bit>();

    // Local Vars

    Word address;
    Byte OPCode;
    Byte product;
    Byte X;

    // Configure CPU

    cpu.PC = PC;
    cpu.C = C;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x2E;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ABX addressing mode test config") {

        // Config

        OPCode = 0x3E;
        address = random<Word>(0x5000, 0x7FFF);
        X = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = (address - X) >> 8;
        mem[PC + 2] = address - X;

        // Config Register

        cpu.X = X;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0x26;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    SECTION("ZPX addressing mode test config") {

        // Config

        OPCode = 0x36;
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

    // Product

    product = (Byte) ((value * 2) + C);

    // Assertions

    REQUIRE(mem[address] == product);
    REQUIRE(cpu.Z == isZero(product));
    REQUIRE(cpu.N == isNegative(product));
    REQUIRE(cpu.C == isNegative(value));

}