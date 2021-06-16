#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Read Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word address;

    Byte byteValue;
    Word wordValue;

    SECTION("at random address for one byte") {
        
        address = random<Word>(0x5000, 0x7FFF);
        byteValue = random<Byte>();

        mem[address] = byteValue;

        REQUIRE(cpu.Read<Byte>(address) == byteValue);
    };

    SECTION("at random address for two bytes") {
        
        address = random<Word>(0x5000, 0x7FFF);
        wordValue = random<Word>();

        mem[address] = (Byte) (wordValue >> 8);
        mem[address + 1] = (Byte) wordValue;

        REQUIRE(cpu.Read<Word>(address) == wordValue);
    };
}