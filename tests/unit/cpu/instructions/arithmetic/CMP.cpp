#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("CMP instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Byte A;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xC9, 0xC5, 0xD5, 0xCD, 0xDD, 
            0xD9, 0xC1, 0xD1
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == CMP);
        }
    };

    SECTION("executes properly when equal") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>();
        A = value;

        cpu.A = A;

        mem[address] = value;

        cpu.Execute(CMP, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 1);
    };

    SECTION("executes properly when less then and negative") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(1, 255);
        A = value - 1;

        cpu.A = A;

        mem[address] = value;

        cpu.Execute(CMP, address);

        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when less then and positive") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(-1, -127);
        A = value - 129;

        cpu.A = A;

        mem[address] = value;

        cpu.Execute(CMP, address);

        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when greater then and negative") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(0, 127);
        A = value + 128;

        cpu.A = A;

        mem[address] = value;

        cpu.Execute(CMP, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly when greater then and postive") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(1, 254);
        A = value + 1;

        cpu.A = A;

        mem[address] = value;

        cpu.Execute(CMP, address);

        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };
}