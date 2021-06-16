#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isClear function") {

    // Vars

    Bit value;

    SECTION("returns proper value for set bit") {

        value = 1;

        REQUIRE(isClear(value) == 0);
    };

    SECTION("returns proper value for cleared bit") {

        value = 0;

        REQUIRE(isClear(value) == 1);
    };
}