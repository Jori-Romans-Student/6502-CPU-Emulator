#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("DEC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[4] = { 
            0xC6, 0xD6, 0xCE, 0xDE
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == DEC);
        }
    };

    SECTION("decrements random value") {

        address = (Word) rand();
        value = (Byte) rand();

        mem[address] = value;

        cpu.Execute(DEC, address);

        REQUIRE(mem[address] == value - 1);
    };

    SECTION("decrements value to zero") {

        address = (Word) rand();
        value = (Byte) 0x01;

        mem[address] = value;

        cpu.Execute(DEC, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
    };

    SECTION("decrements value to negative") {

        address = (Word) rand();
        value = (Byte) 0x00;

        mem[address] = value;

        cpu.Execute(DEC, address);

        REQUIRE(mem[address] == 0xFF);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
    };

    SECTION("decrements value to positive") {

        address = (Word) rand();
        value = (Byte) 0x80;

        mem[address] = value;

        cpu.Execute(DEC, address);

        REQUIRE(mem[address] == 0x7F);
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
    };
}