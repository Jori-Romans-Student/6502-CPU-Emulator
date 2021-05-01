#include "catch2/catch.hpp"

int Seven() {
    return 7;
}

TEST_CASE( "Test Number Function" ) {
    REQUIRE( Seven() == 7 );
}