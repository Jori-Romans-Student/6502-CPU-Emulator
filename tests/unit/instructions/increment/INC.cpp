#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("INC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[4] = { 
            0xE6, 0xF6, 0xEE, 0xFE
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == INC);
        }
    };

    SECTION("increments random value") {

        address = random<Word>();
        value = random<Byte>();

        mem[address] = value;

        cpu.Execute(INC, address);

        REQUIRE(mem[address] == value + 1);
    };

    SECTION("increments value to zero") {

        address = random<Word>();
        value = 0xFF;

        mem[address] = value;

        cpu.Execute(INC, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("increments value to negative") {

        address = random<Word>();
        value = 0x7F;

        mem[address] = value;

        cpu.Execute(INC, address);

        REQUIRE(mem[address] == 0x80);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };

    SECTION("increments value to positive") {

        address = random<Word>();
        value = 0x00;

        mem[address] = value;

        cpu.Execute(INC, address);

        REQUIRE(mem[address] == 0x01);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };
}