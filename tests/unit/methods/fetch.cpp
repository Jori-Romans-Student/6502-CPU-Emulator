#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Fetch Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word PC;

    Byte byteValue;
    Word wordValue;

    SECTION("at random PC for one byte") {
        PC = (Word) rand();
        byteValue = (Byte) rand();

        cpu.PC = PC;
        mem[PC] = byteValue;

        REQUIRE(cpu.Fetch<Byte>() == byteValue);
    };

    SECTION("at random PC for two bytes") {
        PC = (Word) rand();
        wordValue = (Word) rand();

        cpu.PC = PC;
        mem[PC] = (Byte) (wordValue >> 8);
        mem[PC + 1] = (Byte) wordValue;

        REQUIRE(cpu.Fetch<Word>() == wordValue);
    };
}