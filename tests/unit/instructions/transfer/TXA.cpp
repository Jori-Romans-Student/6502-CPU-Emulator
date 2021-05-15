#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("TXA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte value;
    Byte address;
    Byte X;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x8A
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TXA);
        }
    };

    SECTION("executes properly on zero value") {

        address = (Byte) 0x00;
        X = (Byte) 0x00;

        cpu.X = X;

        cpu.Execute(TXA, address);

        REQUIRE(cpu.A == X);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = (Byte) 0x00;
        X = (Byte) 0x57;

        cpu.X = X;

        cpu.Execute(TXA, address);

        REQUIRE(cpu.A == X);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = (Byte) 0x00;
        X = (Byte) 0xBA;

        cpu.X = X;

        cpu.Execute(TXA, address);

        REQUIRE(cpu.A == X);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}