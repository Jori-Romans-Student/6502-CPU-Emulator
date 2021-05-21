#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ROR instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x6A, 0x66, 0x76, 0x6E, 0x7E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ROR);
        }
    };

    SECTION("shift to zero with no carry") {

        address = (Word) rand();
        value = (Byte) 0x00;
        C = 0;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROR, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift to zero with carry") {

        address = (Word) rand();
        value = (Byte) 0x01;
        C = 0;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROR, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random odd value") {

        address = (Word) rand();
        value = (Byte) rand() | 0x03;
        C = rand() % 2;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROR, address);

        REQUIRE(mem[address] == (Byte) ((value / 2) + (C * 128)));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == C);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random even value") {

        address = (Word) rand();
        value = (Byte) (rand() | 0x02) & 0xFE;
        C = rand() % 2;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROR, address);

        REQUIRE(mem[address] == (Byte) ((value / 2) + (C * 128)));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == C);
        REQUIRE(cpu.C == 0);
    };
}