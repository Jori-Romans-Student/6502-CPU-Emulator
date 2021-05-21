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
        
        address = (Word) rand();
        byteValue = (Byte) rand();

        mem[address] = byteValue;

        REQUIRE(cpu.Read<Byte>(address) == byteValue);
    };

    SECTION("at random address for two bytes") {
        
        address = (Word) rand();
        wordValue = (Word) rand();

        mem[address] = (Byte) (wordValue >> 8);
        mem[address + 1] = (Byte) wordValue;

        REQUIRE(cpu.Read<Word>(address) == wordValue);
    };
}