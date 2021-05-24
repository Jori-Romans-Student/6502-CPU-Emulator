#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LDY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0xA0, 0xA4, 0xB4, 0xAC, 0xBC 
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == LDY);
        }
    };

    SECTION("executes properly on zero value") {

        address = random<Word>();
        value = 0x00;

        mem[address] = value;

        cpu.Execute(LDY, address);

        REQUIRE(cpu.Y == value);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = random<Word>();
        value = random<Byte>(1, 127);

        mem[address] = value;

        cpu.Execute(LDY, address);

        REQUIRE(cpu.Y == value);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = random<Word>();
        value = random<Byte>(-1, -128);

        mem[address] = value;

        cpu.Execute(LDY, address);

        REQUIRE(cpu.Y == value);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}