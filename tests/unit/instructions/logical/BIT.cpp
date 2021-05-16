#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("BIT instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte A;
    Byte value;
    Word address;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[2] = { 
            0x24, 0x2C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == BIT);
        }
    };

    SECTION("sets zero value appropriately") {

        address = (Word) rand();
        A = (Byte) rand() | 0x01;
        cpu.A = A;

        mem[address] = (Byte) 0x00;
        cpu.Execute(BIT, address);
        REQUIRE(cpu.Z == 1);

        mem[address] = (Byte) rand() | 0x01;
        cpu.Execute(BIT, address);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("sets N and V flags to positive on proper value") {

        value = (Byte) rand() | 0xC0; // gurantees positive flags
        address = (Word) rand();

        mem[address] = value;

        cpu.Execute(BIT, address);

        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.V == 1);
    };

    SECTION("sets N and V flags to positive on proper value") {

        value = (Byte) rand() & 0x3F; // gurantees negative flags
        address = (Word) rand();

        mem[address] = value;

        cpu.Execute(BIT, address);

        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.V == 0);
    };
}