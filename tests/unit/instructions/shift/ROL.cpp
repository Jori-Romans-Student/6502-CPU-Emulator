#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ROL instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Byte C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[5] = { 
            0x2A, 0x26, 0x36, 0x2E, 0x3E
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ROL);
        }
    };

    SECTION("shift to zero with no carry") {

        address = (Word) rand();
        value = (Byte) 0x00;
        C = 0;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROL, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift to zero with carry") {

        address = (Word) rand();
        value = (Byte) 0x80;
        C = 0;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROL, address);

        REQUIRE(mem[address] == 0x00);
        REQUIRE(cpu.Z == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random small positive value") {

        address = (Word) rand();
        value = (Byte) (rand() & 0x3F) | 0x01;
        C = rand() % 2;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROL, address);

        REQUIRE(mem[address] == (Byte) ((value * 2) + C));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift random large positive value") {

        address = (Word) rand();
        value = (Byte) (rand() & 0x7F) | 0x41;
        C = rand() % 2;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROL, address);

        REQUIRE(mem[address] == (Byte) ((value * 2) + C));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.C == 0);
    };

    SECTION("shift random small negative value") {

        address = (Word) rand();
        value = (Byte) rand() | 0xC1;
        C = rand() % 2;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROL, address);

        REQUIRE(mem[address] == (Byte) ((value * 2) + C));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.C == 1);
    };

    SECTION("shift random large negative value") {

        address = (Word) rand();
        value = (Byte) (rand() & 0x3F) | 0x81;
        C = rand() % 2;

        cpu.C = C;
        mem[address] = value;

        cpu.Execute(ROL, address);

        REQUIRE(mem[address] == (Byte) ((value * 2) + C));
        REQUIRE(cpu.Z == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.C == 1);
    };
}