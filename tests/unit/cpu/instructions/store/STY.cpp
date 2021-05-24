#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("STY instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    
    Word address;
    Bit Y;

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

        address = random<Word>();
        Y = random<Byte>();
        cpu.Y = Y;

        cpu.Execute(STY, address);

        REQUIRE(cpu.Read<Byte>(address) == Y);
    };
}