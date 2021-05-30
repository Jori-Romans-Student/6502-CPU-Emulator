#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("INX Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>(0x1000, 0x3FFF);
    Byte value = random<Byte>();

    // Local Vars

    Word address;
    Byte sum;
    Byte OPCode;
    Byte X;

    // Configure CPU

    cpu.PC = PC;

    SECTION("IMP addressing mode test config") {

        // Config

        OPCode = 0xE8;
        X = value;
        cpu.X = X;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Sum

    sum = (Byte) (value + 1);

    // Assertions

    REQUIRE(cpu.X == sum);
    REQUIRE(cpu.N == isNegative(sum));
    REQUIRE(cpu.Z == isZero(sum));

}