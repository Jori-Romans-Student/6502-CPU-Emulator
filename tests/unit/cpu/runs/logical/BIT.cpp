#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BIT Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();
    Byte A = random<Byte>();

    // Local Vars

    Word address;
    Byte OPCode;

    // Configure CPU

    cpu.A = A;
    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x2C;
        address = random<Word>(0x5000, 0x7FFF);

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ZP addressing mode test config") {

        // Config

        OPCode = 0x24;
        address = random<Byte>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.Z == isZero(A & value));
    REQUIRE(cpu.N == isNegative(value));
    REQUIRE(cpu.V == isOverflow(value));

}