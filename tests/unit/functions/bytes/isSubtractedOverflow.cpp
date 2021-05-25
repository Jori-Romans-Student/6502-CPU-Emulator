#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("isSubtractedOverflow function") {

    // Vars

    Byte valueOne;
    Byte valueTwo;

    SECTION("returns proper value for positive values") {

        valueOne = random<Byte>(0, 127);
        valueTwo = random<Byte>(0, 127);

        REQUIRE(isSubtractedOverflow(valueOne, valueTwo) == 0);
    };

    SECTION("returns proper value for negative values") {

        valueOne = random<Byte>(-1, -128);
        valueTwo = random<Byte>(-1, -128);

        REQUIRE(isSubtractedOverflow(valueOne, valueTwo) == 0);
    };

    SECTION("returns proper value for for positive minus negative overflow") {

        valueOne = random<Byte>(65, 127);
        valueTwo = random<Byte>(-65, -127);

        REQUIRE(isSubtractedOverflow(valueOne, valueTwo) == 1);
    };

    SECTION("returns proper value for for positive minus negative non-overflow") {

        valueOne = random<Byte>(1, 63);
        valueTwo = random<Byte>(-1, -63);

        REQUIRE(isSubtractedOverflow(valueOne, valueTwo) == 0);
    };

    SECTION("returns proper value for for negative minus positive overflow") {

        valueOne = random<Byte>(-65, -127);
        valueTwo = random<Byte>(65, 127);

        REQUIRE(isSubtractedOverflow(valueOne, valueTwo) == 1);
    };

    SECTION("returns proper value for for negative minus positive non-overflow") {

        valueOne = random<Byte>(-1, -63);
        valueTwo = random<Byte>(1, 63);

        REQUIRE(isSubtractedOverflow(valueOne, valueTwo) == 0);
    };

}