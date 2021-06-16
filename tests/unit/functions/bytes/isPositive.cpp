#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isPositive function") {

    // Vars

    Byte value;

    SECTION("returns proper value for zero byte") {

        value = random<Byte>(0, 0);

        REQUIRE(isPositive(value) == 1);
    };

    SECTION("returns proper value for positive byte") {

        value = random<Byte>(1, 127);

        REQUIRE(isPositive(value) == 1);
    };

    SECTION("returns proper value for negative byte") {

        value = random<Byte>(-1, -128);

        REQUIRE(isPositive(value) == 0);
    };
}