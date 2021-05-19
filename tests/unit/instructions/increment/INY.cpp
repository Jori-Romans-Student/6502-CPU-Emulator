#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("INY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte Y;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xC8
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == INY);
        }
    };

    SECTION("increments value to zero") {

        Y = (Byte) 0xFF;

        cpu.Y = Y;

        cpu.Execute(INY, 0x00);

        REQUIRE(cpu.Y == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("increments value to negative") {

        address = (Word) rand();
        Y = (Byte) 0x7F;

        cpu.Y = Y;

        cpu.Execute(INY, 0x00);

        REQUIRE(cpu.Y == 0x80);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };

    SECTION("increments value to positive") {

        address = (Word) rand();
        Y = (Byte) 0x00;

        cpu.Y = Y;

        cpu.Execute(INY, 0x00);

        REQUIRE(cpu.Y == 0x01);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };
}