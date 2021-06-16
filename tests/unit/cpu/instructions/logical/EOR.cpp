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

        value = random<Byte>();
        address = random<Word>(0x5000, 0x7FFF);
        A = value; // ensure matching so XOR return 0
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(EOR, address);

        REQUIRE(cpu.A == (value ^ A));
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on positive value") {

        value = random<Byte>(-1, -128) | 1; // gurantees EOR positive and non zero
        address = random<Word>(0x5000, 0x7FFF);
        A = random<Byte>(-1, -128) & 0xFE; // gurantees EOR positive and non zero
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(EOR, address);

        REQUIRE(cpu.A == (value ^ A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };

    SECTION("executes properly on negative value") {

        value = random<Byte>(1, 127) | 1; // gurantees EOR negative
        address = random<Word>(0x5000, 0x7FFF);
        A = random<Byte>(-1, -128) & 0xFE; // gurantees EOR negative
        cpu.A = A;

        mem[address] = value;

        cpu.Execute(EOR, address);

        REQUIRE(cpu.A == (value ^ A));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };
}