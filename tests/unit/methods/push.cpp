#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Push Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte byteValue;
    Word wordValue;

    Byte S;

    SECTION("with random value for one byte") {

        byteValue = random<Byte>();
        S = 0x00;
        cpu.S = S;

        cpu.Push<Byte>(byteValue);

        REQUIRE(mem[0x0100 | S] == byteValue);
        REQUIRE(cpu.S == S + 1);
    };

    SECTION("with random value for two bytes") {

        wordValue = random<Word>();
        S = 0x00;
        cpu.S = S;

        cpu.Push<Word>(wordValue);

        REQUIRE(mem[0x0100] == (Byte) (wordValue >> 8));
        REQUIRE(mem[0x0101] == (Byte) wordValue);
        REQUIRE(cpu.S == S + 2);
    };
}