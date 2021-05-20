#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("DEY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte Y;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x88
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == DEY);
        }
    };

    SECTION("decrements value to zero") {

        Y = (Byte) 0x01;

        cpu.Y = Y;

        cpu.Execute(DEY, 0x00);

        REQUIRE(cpu.Y == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("decrements value to negative") {

        address = (Word) rand();
        Y = (Byte) 0x00;

        cpu.Y = Y;

        cpu.Execute(DEY, 0x00);

        REQUIRE(cpu.Y == 0xFF);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };

    SECTION("decrements value to positive") {

        address = (Word) rand();
        Y = (Byte) 0x80;

        cpu.Y = Y;

        cpu.Execute(DEY, 0x00);

        REQUIRE(cpu.X == 0x7F);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };
}