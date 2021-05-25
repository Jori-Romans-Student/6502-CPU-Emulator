#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isAddedOverflow function") {

    // Vars

    Byte valueOne;
    Byte valueTwo;

    SECTION("returns proper value for positive and negative values") {

        valueOne = random<Byte>(0, 127);
        valueTwo = random<Byte>(-1, -128);

        REQUIRE(isAddedOverflow(valueOne, valueTwo) == 0);
    };

    SECTION("returns proper value for positive values and positive sum") {

        valueOne = random<Byte>(0, 63);
        valueTwo = random<Byte>(0, 63);

        REQUIRE(isAddedOverflow(valueOne, valueTwo) == 0);
    };

    SECTION("returns proper value for positive values and negative sum") {

        valueOne = random<Byte>(64, 127);
        valueTwo = random<Byte>(64, 127);

        REQUIRE(isAddedOverflow(valueOne, valueTwo) == 1);
    };

    SECTION("returns proper value for negative values and negative sum") {

        valueOne = random<Byte>(-1, -64);
        valueTwo = random<Byte>(-1, -64);

        REQUIRE(isAddedOverflow(valueOne, valueTwo) == 0);
    };

    SECTION("returns proper value for negative values and positive sum") {

        valueOne = random<Byte>(-65, -127);
        valueTwo = random<Byte>(-65, -127);

        REQUIRE(isAddedOverflow(valueOne, valueTwo) == 1);
    };
}