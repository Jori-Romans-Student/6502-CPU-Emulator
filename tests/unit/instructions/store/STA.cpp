#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("STA instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte A;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[7] = { 
            0x85, 0x95, 0x8D, 0x9D, 0x99,
            0x81, 0x91
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == STA);
        }
    };

    SECTION("executes properly on random value") {

        address = (Word) rand();
        A = (Byte) rand();
        cpu.A = A;

        cpu.Execute(STA, address);

        REQUIRE(cpu.Read<Byte>(address) == A);
    };
}