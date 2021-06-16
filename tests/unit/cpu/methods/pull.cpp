#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Pull Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte byteValue;
    Word wordValue;
    Byte S;

    SECTION("with random value with one byte") {

        Byte byteValue = random<Byte>();
        S = 0x00;
        
        mem[0x0100] = byteValue;

        cpu.S += 1;

        REQUIRE(cpu.Pull<Byte>() == byteValue);
        REQUIRE(cpu.S == S);
    };

    SECTION("with random value with two bytes") {

        Word wordValue = random<Word>();
        S = 0x00;
        
        mem[0x0100] = (Byte) (wordValue >> 8);
        mem[0x0101] = (Byte) wordValue;

        cpu.S += 2;

        REQUIRE(cpu.Pull<Word>() == wordValue);
        REQUIRE(cpu.S == S);
    };
}