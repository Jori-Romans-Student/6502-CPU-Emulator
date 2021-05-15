#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("TSX instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte S;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xBA
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TSX);
        }
    };

    SECTION("executes properly on zero value") {

        S = (Byte) 0x00;
        cpu.S = S;

        cpu.Execute(TSX, 0);

        REQUIRE(cpu.X == S);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        S = (Byte) 0x22;
        cpu.S = S;

        cpu.Execute(TSX, 0);

        REQUIRE(cpu.X == S);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        S = (Byte) 0xF9;
        cpu.S = S;

        cpu.Execute(TSX, 0);

        REQUIRE(cpu.X == S);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}