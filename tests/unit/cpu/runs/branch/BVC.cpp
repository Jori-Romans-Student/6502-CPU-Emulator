#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BVC Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();
    Byte value = random<Byte>();
    Bit V = random<Bit>();

    // Local Vars

    Byte OPCode;
    Word address;
    Byte displacement;

    // Configure CPU

    cpu.V = V;
    cpu.PC = PC;

    SECTION("REL addressing mode test config") {

        // Config

        OPCode = 0x50;
        address = PC + 1;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;
    mem[address] = value;

    // Run based on section parameters

    cpu.Run();

    // Displacement

    isClear(V) ? displacement = value : displacement = 0;

    // Assertions

    REQUIRE(cpu.PC == (PC + 2 + (Signed) displacement));

}