#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BEQ instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Bit Z;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xF0
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BEQ);
        }
    };

    SECTION("executes correctly on non-set zero") {
        
        PC = (Word) rand();
        value = (Byte) rand();
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set zero with zero displacement") {
        
        PC = (Word) rand();
        value = 0x00;
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set zero with positive displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() & 0x7F) | 0x01;
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on set zero with negative displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() | 0x80);
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC - ((value ^ 0xFF) + 1));
    };
}