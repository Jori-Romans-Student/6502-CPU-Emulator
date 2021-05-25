#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isSet function") {

    // Vars

    Bit value;

    SECTION("returns proper value for set bit") {

        value = 1;

        REQUIRE(isSet(value) == 1);
    };

    SECTION("returns proper value for cleared bit") {

        value = 0;

        REQUIRE(isSet(value) == 0);
    };
}