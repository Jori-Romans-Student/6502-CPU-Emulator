#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isZero function") {

    // Vars

    Byte value;

    SECTION("returns proper value for zero byte") {

        value = random<Byte>(0, 0);

        REQUIRE(isZero(value) == 1);
    };

    SECTION("returns proper value for random non-zero byte") {

        value = random<Byte>(1, 255);

        REQUIRE(isZero(value) == 0);
    };
}