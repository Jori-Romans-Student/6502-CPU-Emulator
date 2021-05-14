#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Fetch Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word PC;
    Byte value = (Byte) rand();

    SECTION("at random PC") {
        PC = (Word) rand();

        cpu.PC = PC;
        mem[PC] = value;

        REQUIRE(cpu.Fetch() == value);
    };
}