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

        address = random<Word>(0x5000, 0x7FFF);
        A = random<Byte>(1, 255) | 0x01;
        cpu.A = A;

        mem[address] = 0x00;
        cpu.Execute(BIT, address);
        REQUIRE(cpu.Z == 1);

        mem[address] = random<Byte>(1, 255) | 0x01;
        cpu.Execute(BIT, address);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("sets N and V flags to positive on proper value") {

        value = random<Byte>(192, 255); // gurantees positive flags
        address = random<Word>(0x5000, 0x7FFF);

        mem[address] = value;

        cpu.Execute(BIT, address);

        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.V == 1);
    };

    SECTION("sets N and V flags to positive on proper value") {

        value = random<Byte>(0, 63); // gurantees negative flags
        address = random<Word>(0x5000, 0x7FFF);

        mem[address] = value;

        cpu.Execute(BIT, address);

        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.V == 0);
    };
}