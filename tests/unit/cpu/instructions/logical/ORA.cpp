#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ORA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte A;
    Byte value;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x09, 0x05, 0x15, 0x0D, 0x1D,
            0x19, 0x01, 0x11
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ORA);
        }
    };

    SECTION("executes properly on zero value") {

        value = 0x00;
        address = random<Word>(0x5000, 0x7FFF);
        A = 0x00;
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(ORA, address);

        REQUIRE(cpu.A == (value | A));
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        value = random<Byte>(1, 127); // gurantees positive ORA
        address = random<Word>(0x5000, 0x7FFF);
        A = random<Byte>(1, 127); // gurantees positive ORA
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(ORA, address);

        REQUIRE(cpu.A == (value | A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        value = random<Byte>(-1, -128); // gurantees negative ORA
        address = random<Word>(0x5000, 0x7FFF);
        A = random<Byte>();
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(ORA, address);

        REQUIRE(cpu.A == (value | A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}