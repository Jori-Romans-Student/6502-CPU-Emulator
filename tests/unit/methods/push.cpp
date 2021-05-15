#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Push Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte value;
    Byte S;

    SECTION("with random value") {

        Byte value = (Byte) rand();
        S = cpu.S;

        cpu.Push(value);

        REQUIRE(mem[0x0100 | S] == value);
        REQUIRE(cpu.S == S + 1);
    };
}