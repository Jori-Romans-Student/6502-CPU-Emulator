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

#include "tests/unit/instructions/arithmetic/ADC.cpp"
#include "tests/unit/instructions/arithmetic/CMP.cpp"
#include "tests/unit/instructions/arithmetic/CPX.cpp"
#include "tests/unit/instructions/arithmetic/CPY.cpp"
#include "tests/unit/instructions/arithmetic/SBC.cpp"

#include "tests/unit/instructions/branch/BCC.cpp"
#include "tests/unit/instructions/branch/BCS.cpp"
#include "tests/unit/instructions/branch/BEQ.cpp"
#include "tests/unit/instructions/branch/BMI.cpp"
#include "tests/unit/instructions/branch/BNE.cpp"
#include "tests/unit/instructions/branch/BPL.cpp"
#include "tests/unit/instructions/branch/BVC.cpp"
#include "tests/unit/instructions/branch/BVS.cpp"

#include "tests/unit/instructions/decrement/DEC.cpp"
#include "tests/unit/instructions/decrement/DEX.cpp"
#include "tests/unit/instructions/decrement/DEY.cpp"

#include "tests/unit/instructions/increment/INC.cpp"
#include "tests/unit/instructions/increment/INX.cpp"
#include "tests/unit/instructions/increment/INY.cpp"

#include "tests/unit/instructions/jump/JMP.cpp"
#include "tests/unit/instructions/jump/JSR.cpp"
#include "tests/unit/instructions/jump/RTS.cpp"

#include "tests/unit/instructions/load/LDA.cpp"
#include "tests/unit/instructions/load/LDX.cpp"
#include "tests/unit/instructions/load/LDY.cpp"

#include "tests/unit/instructions/logical/AND.cpp"
#include "tests/unit/instructions/logical/BIT.cpp"
#include "tests/unit/instructions/logical/EOR.cpp"
#include "tests/unit/instructions/logical/ORA.cpp"

#include "tests/unit/instructions/shift/ASL.cpp"
#include "tests/unit/instructions/shift/LSR.cpp"
#include "tests/unit/instructions/shift/ROL.cpp"
#include "tests/unit/instructions/shift/ROR.cpp"

#include "tests/unit/instructions/stack/PHA.cpp"
#include "tests/unit/instructions/stack/PHP.cpp"
#include "tests/unit/instructions/stack/PLA.cpp"
#include "tests/unit/instructions/stack/PLP.cpp"
#include "tests/unit/instructions/stack/TXS.cpp"
#include "tests/unit/instructions/stack/TSX.cpp"

#include "tests/unit/instructions/status/CLC.cpp"
#include "tests/unit/instructions/status/CLD.cpp"
#include "tests/unit/instructions/status/CLI.cpp"
#include "tests/unit/instructions/status/CLV.cpp"
#include "tests/unit/instructions/status/SEC.cpp"
#include "tests/unit/instructions/status/SED.cpp"
#include "tests/unit/instructions/status/SEI.cpp"

#include "tests/unit/instructions/store/STA.cpp"
#include "tests/unit/instructions/store/STX.cpp"
#include "tests/unit/instructions/store/STY.cpp"

#include "tests/unit/instructions/system/BRK.cpp"
#include "tests/unit/instructions/system/NOP.cpp"
#include "tests/unit/instructions/system/RTI.cpp"

#include "tests/unit/instructions/transfer/TAX.cpp"
#include "tests/unit/instructions/transfer/TAY.cpp"
#include "tests/unit/instructions/transfer/TXA.cpp"
#include "tests/unit/instructions/transfer/TYA.cpp"

