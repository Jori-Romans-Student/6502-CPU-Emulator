#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BNE instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Bit Z;

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
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = random<Byte>();
        Z = 1;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared zero with zero displacement") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = 0x00;
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared zero with positive displacement") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = random<Byte>(1, 127);
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on cleared zero with negative displacement") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = random<Byte>(-1, -128);
        Z = 0;

        cpu.PC = PC;
        cpu.Z = Z;

        mem[PC] = value;

        cpu.Execute(BNE, PC);

        REQUIRE(cpu.PC == PC - negative<Byte>(value));
    };
}