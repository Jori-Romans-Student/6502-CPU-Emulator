#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BVC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Byte V;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x50
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BVC);
        }
    };

    SECTION("executes correctly on non-cleared overflow") {
        
        PC = (Word) rand();
        value = (Byte) rand();
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVC, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared overflow with zero displacement") {
        
        PC = (Word) rand();
        value = 0x00;
        V = 0;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVC, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared overflow with positive displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() & 0x7F) | 0x01;
        V = 0;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVC, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on cleared overflow with negative displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() | 0x80);
        V = 0;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVC, PC);

        REQUIRE(cpu.PC == PC - ((value ^ 0xFF) + 1));
    };
}