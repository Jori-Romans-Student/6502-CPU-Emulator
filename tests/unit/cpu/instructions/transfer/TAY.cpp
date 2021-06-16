#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("TAY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Byte value;
    Byte address;
    Byte A;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[1] = { 
            0xA8
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == TAY);
        }
    };

    SECTION("executes properly on zero value") {

        address = 0x00;
        A = 0x00;

        cpu.A = A;

        cpu.Execute(TAY, address);

        REQUIRE(cpu.Y == A);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        address = 0x00;
        A = random<Byte>(1, 127);

        cpu.A = A;

        cpu.Execute(TAY, address);

        REQUIRE(cpu.Y == A);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        address = 0x00;
        A = random<Byte>(-1, -128);

        cpu.A = A;

        cpu.Execute(TAY, address);

        REQUIRE(cpu.Y == A);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}