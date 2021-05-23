#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BCC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x90
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BCC);
        }
    };

    SECTION("executes correctly on non-cleared carry") {
        
        PC = random<Word>();
        value = random<Byte>();
        C = 1;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCC, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared carry with zero displacement") {
        
        PC = random<Word>();
        value = 0x00;
        C = 0;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCC, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on cleared carry with positive displacement") {
        
        PC = random<Word>();
        value = random<Byte>(1, 127);
        C = 0;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCC, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on cleared carry with negative displacement") {
        
        PC = random<Word>();
        value = random<Byte>(-1, -128);
        C = 0;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCC, PC);

        REQUIRE(cpu.PC == PC - negative<Byte>(value));
    };
}