#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LDX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0xA2, 0xA6, 0xB6, 0xAE, 0xBE 
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == LDX);
        }
    };

    SECTION("executes properly on zero value") {

        address = random<Word>();
        value = 0x00;

        mem[address] = value;

        cpu.Execute(LDX, address);

        REQUIRE(cpu.X == value);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = random<Word>();
        value = random<Byte>(1, 127);

        mem[address] = value;

        cpu.Execute(LDX, address);

        REQUIRE(cpu.X == value);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = random<Word>();
        value = random<Byte>(-1, -128);

        mem[address] = value;

        cpu.Execute(LDX, address);

        REQUIRE(cpu.X == value);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}