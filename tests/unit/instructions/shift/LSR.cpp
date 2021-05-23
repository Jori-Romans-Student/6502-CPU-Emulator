#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("LSR instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x4A, 0x46, 0x56, 0x4E, 0x5E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == LSR);
        }
    };

    SECTION("shift to zero with no carry") {

        address = random<Word>();
        value = 0x00;

        mem[address] = value;

        cpu.Execute(LSR, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift to zero with carry") {

        address = random<Word>();
        value = 0x01;

        mem[address] = value;

        cpu.Execute(LSR, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random odd value") {

        address = random<Word>();
        value = random<Byte>() | 1;

        mem[address] = value;

        cpu.Execute(LSR, address);

        REQUIRE(mem[address] == (Byte) (value / 2));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random even value") {

        address = random<Word>();
        value = random<Byte>() & 0xFE;

        mem[address] = value;

        cpu.Execute(LSR, address);

        REQUIRE(mem[address] == (Byte) (value / 2));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };
}