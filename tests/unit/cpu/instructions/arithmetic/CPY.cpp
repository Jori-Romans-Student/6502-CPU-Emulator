#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CPY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Byte Y;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[3] = { 
            0xC0, 0xC4, 0xCC
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CPY);
        }
    };

    SECTION("executes properly when equal") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>();
        Y = value;

        cpu.Y = Y;

        mem[address] = value;

        cpu.Execute(CPY, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 1);
    };

    SECTION("executes properly when less then and negative") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(1, 255);
        Y = value - 1;

        cpu.Y = Y;

        mem[address] = value;

        cpu.Execute(CPY, address);

        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when less then and positive") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(-1, -127);
        Y = value - 129;

        cpu.Y = Y;

        mem[address] = value;

        cpu.Execute(CPY, address);

        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when greater then and negative") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(0, 127);
        Y = value + 128;

        cpu.Y = Y;

        mem[address] = value;

        cpu.Execute(CPY, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when greater then and postive") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(1, 254);
        Y = value + 1;

        cpu.Y = Y;

        mem[address] = value;

        cpu.Execute(CPY, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };
}