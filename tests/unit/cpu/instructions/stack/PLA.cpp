#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("PLA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x68
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == PLA);
        }
    };

    SECTION("executes properly on zero value") {
        value = 0x00;
        mem[0x0100] = value;
        cpu.S += 1;

        cpu.Execute(PLA, 0);

        REQUIRE(cpu.A == value);
        REQUIRE(cpu.S == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {
        value = random<Byte>(1, 127);
        mem[0x0100] = value;
        cpu.S += 1;

        cpu.Execute(PLA, 0);

        REQUIRE(cpu.A == value);
        REQUIRE(cpu.S == 0x00);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {
        value = random<Byte>(-1, -128);
        mem[0x0100] = value;
        cpu.S += 1;

        cpu.Execute(PLA, 0);

        REQUIRE(cpu.A == value);
        REQUIRE(cpu.S == 0x00);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}