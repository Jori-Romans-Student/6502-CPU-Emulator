#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ASL instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x0A, 0x06, 0x16, 0x0E, 0x1E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ASL);
        }
    };

    SECTION("shift to zero with no carry") {

        address = random<Word>();
        value = 0x00;

        mem[address] = value;

        cpu.Execute(ASL, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift to zero with carry") {

        address = random<Word>();
        value = 0x80;

        mem[address] = value;

        cpu.Execute(ASL, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random small positive value") {

        address = random<Word>();
        value = random<Byte>(1, 64);

        mem[address] = value;

        cpu.Execute(ASL, address);

        REQUIRE(mem[address] == (Byte) (value * 2));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift random large positive value") {

        address = random<Word>();
        value = random<Byte>(65, 127);

        mem[address] = value;

        cpu.Execute(ASL, address);

        REQUIRE(mem[address] == (Byte) (value * 2));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift random small negative value") {

        address = random<Word>();
        value = random<Byte>(-1, -64);

        mem[address] = value;

        cpu.Execute(ASL, address);

        REQUIRE(mem[address] == (Byte) (value * 2));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random large negative value") {

        address = random<Word>();
        value = random<Byte>(-65, -128);

        mem[address] = value;

        cpu.Execute(ASL, address);

        REQUIRE(mem[address] == (Byte) (value * 2));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };
}