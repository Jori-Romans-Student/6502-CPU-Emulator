#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("JMP Run Tests") {

    // Initialize Hardware

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    // Global Vars

    Word PC = random<Word>();

    // Local Vars

    Word address;
    Byte addressOfAddress;
    Byte OPCode;

    // Configure CPU

    cpu.PC = PC;

    SECTION("AB addressing mode test config") {

        // Config

        OPCode = 0x4C;
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = address >> 8;
        mem[PC + 2] = address;

    };

    SECTION("ID addressing mode test config") {

        // Config

        OPCode = 0x6C;
        addressOfAddress = random<Word>();
        address = random<Word>();

        // Memory config for absolute addressing mode

        mem[PC + 1] = addressOfAddress >> 8;
        mem[PC + 2] = addressOfAddress;
        mem[addressOfAddress] = address >> 8;
        mem[addressOfAddress + 1] = address;

    };

    // Set memory locations based on section parameters

    mem[PC] = OPCode;

    // Run based on section parameters

    cpu.Run();

    // Assertions

    REQUIRE(cpu.PC == address);

}