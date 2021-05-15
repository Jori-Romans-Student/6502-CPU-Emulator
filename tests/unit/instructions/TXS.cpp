#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("TXS instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte X;
    Byte address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0x9A
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TXS);
        }
    };

    SECTION("executes properly on zero value") {

        address = 0x00;
        X = (Byte) 0x00;
        cpu.X = X;

        cpu.Execute(TXS, address);

        REQUIRE(mem[0x0100] == X);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = 0x00;
        X = (Byte) 0x72;
        cpu.X = X;

        cpu.Execute(TXS, address);

        REQUIRE(mem[0x0100] == X);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = 0x00;
        X = (Byte) 0xD9;
        cpu.X = X;

        cpu.Execute(TXS, address);

        REQUIRE(mem[0x0100] == X);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}