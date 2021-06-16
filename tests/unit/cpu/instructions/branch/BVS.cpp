#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BVS instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Bit V;

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
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = random<Byte>();
        V = 0;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set overflow with zero displacement") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = 0x00;
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set overflow with positive displacement") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = random<Byte>(1, 127);
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on set overflow with negative displacement") {
        
        PC = random<Word>(0x1000, 0x3FFF);
        value = random<Byte>(-1, -128);
        V = 1;

        cpu.PC = PC;
        cpu.V = V;

        mem[PC] = value;

        cpu.Execute(BVS, PC);

        REQUIRE(cpu.PC == PC - negative<Byte>(value));
    };
}