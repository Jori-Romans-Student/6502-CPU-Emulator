#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("ADC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Byte A;
    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0x69, 0x65, 0x75, 0x6D, 0x7D, 
            0x79, 0x61, 0x71
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == ADC);
        }
    };

    SECTION("executes properly on zero sum") {

        address = (Word) rand();
        value = (Byte) (rand() & 0x7F); // ensures a positive value
        A = (value ^ 0xFF) + 0x01; // ensures a negative value matching positive value
        C = 0;

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(ADC, address);

        REQUIRE(cpu.A == 0x00);
        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 1);
    };

    SECTION("executes properly on positive overflow") {

        address = (Word) rand();
        value = (Byte) (rand() & 0x7F) | 0x40; // ensures a positive value greater then 64
        A = (Byte) (rand() & 0x7F) | 0x40; // ensures a positive value greater then 64
        C = rand() % 2;

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(ADC, address);

        REQUIRE(cpu.A == (Byte)(A + value + C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 1);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on positive non-overflow") {

        address = (Word) rand();
        value = (Byte) (rand() & 0x3F); // ensures a positive value less then 64
        A = (Byte) (rand() & 0x3F); // ensures a positive value less then 64
        C = rand() % 2;

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(ADC, address);

        REQUIRE(cpu.A == (Byte)(A + value + C));
        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on negative overflow") {

        address = (Word) rand();
        value = (Byte) (rand() | 0x80) & 0xBF; // ensures a negative value greater then -64
        A = (Byte) (rand() | 0x80) & 0xBF; // ensures a negative value greater then -64
        C = rand() % 2;

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(ADC, address);

        REQUIRE(cpu.A == (Byte)(A + value + C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on negative non-overflow") {

        address = (Word) rand();
        value = (Byte) (rand() | 0xC0); // ensures a negative value less then -64
        A = (Byte) (rand() | 0xC0); // ensures a negative value less then -64
        C = rand() % 2;

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(ADC, address);

        REQUIRE(cpu.A == (Byte)(A + value + C));
        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };
}