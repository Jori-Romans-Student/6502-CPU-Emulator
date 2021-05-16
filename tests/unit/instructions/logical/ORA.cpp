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

        value = (Byte) 0x00;
        address = (Word) rand();
        A = (Byte) 0x00;
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(ORA, address);

        REQUIRE(cpu.A == (value | A));
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        value = (Byte) rand() & 0x7F; // gurantees positive ORA
        address = (Word) rand();
        A = (Byte) rand() & 0x7F; // gurantees positive ORA
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(ORA, address);

        REQUIRE(cpu.A == (value | A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        value = (Byte) rand() | 0x80; // gurantees negative ORA
        address = (Word) rand();
        A = (Byte) rand();
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(ORA, address);

        REQUIRE(cpu.A == (value | A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}