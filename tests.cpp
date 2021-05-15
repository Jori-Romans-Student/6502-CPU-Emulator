#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

// Common Methods

#include "tests/unit/methods/read.cpp"
#include "tests/unit/methods/write.cpp"
#include "tests/unit/methods/fetch.cpp"
#include "tests/unit/methods/pull.cpp"
#include "tests/unit/methods/push.cpp"

// Addressing

#include "tests/unit/addressing/AB.cpp"
#include "tests/unit/addressing/ABX.cpp"
#include "tests/unit/addressing/ABY.cpp"
#include "tests/unit/addressing/AC.cpp"
#include "tests/unit/addressing/ID.cpp"
#include "tests/unit/addressing/IDX.cpp"
#include "tests/unit/addressing/IDY.cpp"
#include "tests/unit/addressing/IMM.cpp"
#include "tests/unit/addressing/REL.cpp"
#include "tests/unit/addressing/ZP.cpp"
#include "tests/unit/addressing/ZPX.cpp"
#include "tests/unit/addressing/ZPY.cpp"

// Instructions

#include "tests/unit/instructions/LDA.cpp"
#include "tests/unit/instructions/LDX.cpp"
#include "tests/unit/instructions/LDY.cpp"
#include "tests/unit/instructions/STA.cpp"
#include "tests/unit/instructions/STX.cpp"
#include "tests/unit/instructions/STY.cpp"
#include "tests/unit/instructions/TAX.cpp"
#include "tests/unit/instructions/TAY.cpp"
#include "tests/unit/instructions/TSX.cpp"
#include "tests/unit/instructions/TXA.cpp"
#include "tests/unit/instructions/TYA.cpp"

