#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BNE instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Byte Z;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xD0
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BNE);
        }
    };

    SECTION("executes correctly on non-cleared zero") {
        
        PC = (Word) rand();
        value = (Byte) rand();
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared zero with zero displacement") {
        
        PC = (Word) rand();
        value = 0x00;
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared zero with positive displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() & 0x7F) | 0x01;
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on cleared zero with negative displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() | 0x80);
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC - ((value ^ 0xFF) + 1));
    };
}