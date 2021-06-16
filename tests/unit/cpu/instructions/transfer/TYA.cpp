#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("TYA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte value;
    Byte address;
    Byte Y;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x98
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TYA);
        }
    };

    SECTION("executes properly on zero value") {

        address = 0x00;
        Y = 0x00;

        cpu.Y = Y;

        cpu.Execute(TYA, address);

        REQUIRE(cpu.A == Y);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = 0x00;
        Y = random<Byte>(1, 127);

        cpu.Y = Y;

        cpu.Execute(TYA, address);

        REQUIRE(cpu.A == Y);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = 0x00;
        Y = random<Byte>(-1, -128);

        cpu.Y = Y;

        cpu.Execute(TYA, address);

        REQUIRE(cpu.A == Y);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}