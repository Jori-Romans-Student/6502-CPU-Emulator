#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

#include "tests/unit/index.cpp" // Unit Tests

int main( int argc, char* argv[] ) {

  // global setup...

  srand(time(NULL));

  int result = Catch::Session().run( argc, argv );

  // global clean-up...

  return result;

}