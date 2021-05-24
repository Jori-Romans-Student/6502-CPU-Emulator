#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BCS instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word PC;
    Byte value;
    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xB0
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BCS);
        }
    };

    SECTION("executes correctly on non-set carry") {
        
        PC = random<Word>();
        value = random<Byte>();
        C = 0;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCS, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set carry with zero displacement") {
        
        PC = random<Word>();
        value = 0x00;
        C = 1;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCS, PC);

        REQUIRE(cpu.PC == PC);
    };

    SECTION("executes correctly on set carry with positive displacement") {
        
        PC = random<Word>();
        value = random<Byte>(1, 127);
        C = 1;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCS, PC);

        REQUIRE(cpu.PC == PC + value);
    };

    SECTION("executes correctly on set carry with negative displacement") {
        
        PC = random<Word>();
        value = random<Byte>(-1, -128);
        C = 1;

        cpu.PC = PC;
        cpu.C = C;

        mem[PC] = value;

        cpu.Execute(BCS, PC);

        REQUIRE(cpu.PC == PC - negative<Byte>(value));
    };
}