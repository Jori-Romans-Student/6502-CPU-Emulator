#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BMI instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Bit N;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x30
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BMI);
        }
    };

    SECTION("executes correctly on non-set negative") {
        
        PC = random<Word>();
        value = random<Byte>();
        N = 0;

        cpu.PC = PC;
        cpu.N = N;

        mem[PC] = value;

        cpu.Execute(BMI, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set negative with zero displacement") {
        
        PC = random<Word>();
        value = 0x00;
        N = 1;

        cpu.PC = PC;
        cpu.N = N;

        mem[PC] = value;

        cpu.Execute(BMI, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set negative with positive displacement") {
        
        PC = random<Word>();
        value = random<Byte>(1, 127);
        N = 1;

        cpu.PC = PC;
        cpu.N = N;

        mem[PC] = value;

        cpu.Execute(BMI, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on set negative with negative displacement") {
        
        PC = random<Word>();
        value = random<Byte>(-1, -128);
        N = 1;

        cpu.PC = PC;
        cpu.N = N;

        mem[PC] = value;

        cpu.Execute(BMI, PC);

        REQUIRE(cpu.PC == PC - negative<Byte>(value));
    };
}