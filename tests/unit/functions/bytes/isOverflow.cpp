#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isOverflow function") {

    // Vars

    Byte value;

    SECTION("returns proper value for overflow byte") {

        value = random<Byte>() | 0x40;

        REQUIRE(isOverflow(value) == 1);
    };

    SECTION("returns proper value for random non-overflow byte") {

        value = random<Byte>() & 0xBF;

        REQUIRE(isOverflow(value) == 0);
    };
}