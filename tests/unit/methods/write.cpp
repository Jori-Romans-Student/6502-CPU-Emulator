#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Write Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);
    Word address;
    Byte value = (Byte) rand();

    SECTION("at random address") {
        address = (Word) rand();

        cpu.Write(address, value);

        REQUIRE(mem[address] == value);
    };
}