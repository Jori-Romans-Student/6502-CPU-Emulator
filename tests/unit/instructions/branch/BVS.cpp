#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BVS instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Byte V;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x70
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BVS);
        }
    };

    SECTION("executes correctly on non-set overflow") {
        
        PC = (Word) rand();
        value = (Byte) rand();
        V = 0;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set overflow with zero displacement") {
        
        PC = (Word) rand();
        value = 0x00;
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set overflow with positive displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() & 0x7F) | 0x01;
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on set overflow with negative displacement") {
        
        PC = (Word) rand();
        value = (Byte) (rand() | 0x80);
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC - ((value ^ 0xFF) + 1));
    };
}