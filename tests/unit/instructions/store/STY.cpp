#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("STY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Word address;
    Byte Y;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[3] = { 
            0x84, 0x94, 0x8C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == STY);
        }
    };

    SECTION("executes properly on random value") {

        address = (Word) rand();
        Y = (Byte) rand();
        cpu.Y = Y;

        cpu.Execute(STY, address);

        REQUIRE(cpu.Read(address) == Y);
    };
}