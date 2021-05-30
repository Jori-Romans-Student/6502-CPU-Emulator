#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("DEX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte X;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xCA
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == DEX);
        }
    };

    SECTION("decrements value to zero") {

        X = 0x01;

        cpu.X = X;

        cpu.Execute(DEX, 0x00);

        REQUIRE(cpu.X == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("decrements value to negative") {

        address = random<Word>(0x5000, 0x7FFF);
        X = 0x00;

        cpu.X = X;

        cpu.Execute(DEX, 0x00);

        REQUIRE(cpu.X == 0xFF);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };

    SECTION("decrements value to positive") {

        address = random<Word>(0x5000, 0x7FFF);
        X = 0x80;

        cpu.X = X;

        cpu.Execute(DEX, 0x00);

        REQUIRE(cpu.X == 0x7F);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };
}