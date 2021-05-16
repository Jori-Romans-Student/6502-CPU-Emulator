#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("EOR instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte A;
    Byte value;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x49, 0x45, 0x55, 0x4D, 0x5D,
            0x59, 0x41, 0x51
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == EOR);
        }
    };

    SECTION("executes properly on zero value") {

        value = (Byte) rand();
        address = (Word) rand();
        A = value; // ensure matching so XOR return 0
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(EOR, address);

        REQUIRE(cpu.A == (value ^ A));
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        value = (Byte) ((rand() | 0x80) & 0xFE); // gurantees EOR positive and non zero
        address = (Word) rand();
        A = (Byte) rand() | 0x81; // gurantees EOR positive and non zero
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(EOR, address);

        REQUIRE(cpu.A == (value ^ A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        value = (Byte) (rand() & 0x7F); // gurantees EOR negative
        address = (Word) rand();
        A = (Byte) rand() | 0x80; // gurantees EOR negative
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(EOR, address);

        REQUIRE(cpu.A == (value ^ A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}