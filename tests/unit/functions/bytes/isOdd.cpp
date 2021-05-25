#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isOdd function") {

    // Vars

    Byte value;

    SECTION("returns proper value for even byte") {

        value = random<Byte>() & 0xFE;

        REQUIRE(isOdd(value) == 0);
    };

    SECTION("returns proper value for odd byte") {

        value = random<Byte>() | 0x01;

        REQUIRE(isOdd(value) == 1);
    };
}