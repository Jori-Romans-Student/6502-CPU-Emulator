#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Pull Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Byte value;
    Byte S;

    SECTION("with random value") {

        Byte value = (Byte) rand();
        S = (Byte) 0x00;
        
        mem[0x0100 | S] = value;

        cpu.S += 1;

        REQUIRE(cpu.Pull() == value);
        REQUIRE(cpu.S == S);
    };
}