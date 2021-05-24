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
        
        PC = random<Word>();
        value = random<Byte>();
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set zero with zero displacement") {
        
        PC = random<Word>();
        value = 0x00;
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set zero with positive displacement") {
        
        PC = random<Word>();
        value = random<Byte>(1, 127);
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on set zero with negative displacement") {
        
        PC = random<Word>();
        value = random<Byte>(-1, -128);
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BEQ, PC);

        REQUIRE(cpu.PC == PC - negative<Byte>(value));
    };
}