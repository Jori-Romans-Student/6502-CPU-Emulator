#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("INX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte X;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xE8
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == INX);
        }
    };

    SECTION("increments value to zero") {

        X = (Byte) 0xFF;

        cpu.X = X;

        cpu.Execute(INX, 0x00);

        REQUIRE(cpu.X == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("increments value to negative") {

        address = (Word) rand();
        X = (Byte) 0x7F;

        cpu.X = X;

        cpu.Execute(INX, 0x00);

        REQUIRE(cpu.X == 0x80);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };

    SECTION("increments value to positive") {

        address = (Word) rand();
        X = (Byte) 0x00;

        cpu.X = X;

        cpu.Execute(INX, 0x00);

        REQUIRE(cpu.X == 0x01);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };
}