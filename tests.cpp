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

#include "tests/unit/instructions/load/LDA.cpp"
#include "tests/unit/instructions/load/LDX.cpp"
#include "tests/unit/instructions/load/LDY.cpp"

#include "tests/unit/instructions/stack/PHA.cpp"
#include "tests/unit/instructions/stack/PHP.cpp"
#include "tests/unit/instructions/stack/PLA.cpp"
#include "tests/unit/instructions/stack/PLP.cpp"
#include "tests/unit/instructions/stack/TXS.cpp"
#include "tests/unit/instructions/stack/TSX.cpp"

#include "tests/unit/instructions/store/STA.cpp"
#include "tests/unit/instructions/store/STX.cpp"
#include "tests/unit/instructions/store/STY.cpp"

#include "tests/unit/instructions/transfer/TAX.cpp"
#include "tests/unit/instructions/transfer/TAY.cpp"
#include "tests/unit/instructions/transfer/TXA.cpp"
#include "tests/unit/instructions/transfer/TYA.cpp"

