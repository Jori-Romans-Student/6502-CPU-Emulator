#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Read Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word address;
    Byte value = (Byte) rand();

    SECTION("at random address") {
        address = (Word) rand();

        mem[address] = value;

        REQUIRE(cpu.Read(address) == value);
    };
}