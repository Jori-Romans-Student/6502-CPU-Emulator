#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch2/catch.hpp"

// Common Methods

#include "tests/unit/cpu/methods/read.cpp"
#include "tests/unit/cpu/methods/write.cpp"
#include "tests/unit/cpu/methods/fetch.cpp"
#include "tests/unit/cpu/methods/pull.cpp"
#include "tests/unit/cpu/methods/push.cpp"

// Addressing

#include "tests/unit/cpu/addressing/AB.cpp"
#include "tests/unit/cpu/addressing/ABX.cpp"
#include "tests/unit/cpu/addressing/ABY.cpp"
#include "tests/unit/cpu/addressing/AC.cpp"
#include "tests/unit/cpu/addressing/ID.cpp"
#include "tests/unit/cpu/addressing/IDX.cpp"
#include "tests/unit/cpu/addressing/IDY.cpp"
#include "tests/unit/cpu/addressing/IMM.cpp"
#include "tests/unit/cpu/addressing/REL.cpp"
#include "tests/unit/cpu/addressing/ZP.cpp"
#include "tests/unit/cpu/addressing/ZPX.cpp"
#include "tests/unit/cpu/addressing/ZPY.cpp"

// Instructions

#include "tests/unit/cpu/instructions/arithmetic/ADC.cpp"
#include "tests/unit/cpu/instructions/arithmetic/CMP.cpp"
#include "tests/unit/cpu/instructions/arithmetic/CPX.cpp"
#include "tests/unit/cpu/instructions/arithmetic/CPY.cpp"
#include "tests/unit/cpu/instructions/arithmetic/SBC.cpp"

#include "tests/unit/cpu/instructions/branch/BCC.cpp"
#include "tests/unit/cpu/instructions/branch/BCS.cpp"
#include "tests/unit/cpu/instructions/branch/BEQ.cpp"
#include "tests/unit/cpu/instructions/branch/BMI.cpp"
#include "tests/unit/cpu/instructions/branch/BNE.cpp"
#include "tests/unit/cpu/instructions/branch/BPL.cpp"
#include "tests/unit/cpu/instructions/branch/BVC.cpp"
#include "tests/unit/cpu/instructions/branch/BVS.cpp"

#include "tests/unit/cpu/instructions/decrement/DEC.cpp"
#include "tests/unit/cpu/instructions/decrement/DEX.cpp"
#include "tests/unit/cpu/instructions/decrement/DEY.cpp"

#include "tests/unit/cpu/instructions/increment/INC.cpp"
#include "tests/unit/cpu/instructions/increment/INX.cpp"
#include "tests/unit/cpu/instructions/increment/INY.cpp"

#include "tests/unit/cpu/instructions/jump/JMP.cpp"
#include "tests/unit/cpu/instructions/jump/JSR.cpp"
#include "tests/unit/cpu/instructions/jump/RTS.cpp"

#include "tests/unit/cpu/instructions/load/LDA.cpp"
#include "tests/unit/cpu/instructions/load/LDX.cpp"
#include "tests/unit/cpu/instructions/load/LDY.cpp"

#include "tests/unit/cpu/instructions/logical/AND.cpp"
#include "tests/unit/cpu/instructions/logical/BIT.cpp"
#include "tests/unit/cpu/instructions/logical/EOR.cpp"
#include "tests/unit/cpu/instructions/logical/ORA.cpp"

#include "tests/unit/cpu/instructions/shift/ASL.cpp"
#include "tests/unit/cpu/instructions/shift/LSR.cpp"
#include "tests/unit/cpu/instructions/shift/ROL.cpp"
#include "tests/unit/cpu/instructions/shift/ROR.cpp"

#include "tests/unit/cpu/instructions/stack/PHA.cpp"
#include "tests/unit/cpu/instructions/stack/PHP.cpp"
#include "tests/unit/cpu/instructions/stack/PLA.cpp"
#include "tests/unit/cpu/instructions/stack/PLP.cpp"
#include "tests/unit/cpu/instructions/stack/TXS.cpp"
#include "tests/unit/cpu/instructions/stack/TSX.cpp"

#include "tests/unit/cpu/instructions/status/CLC.cpp"
#include "tests/unit/cpu/instructions/status/CLD.cpp"
#include "tests/unit/cpu/instructions/status/CLI.cpp"
#include "tests/unit/cpu/instructions/status/CLV.cpp"
#include "tests/unit/cpu/instructions/status/SEC.cpp"
#include "tests/unit/cpu/instructions/status/SED.cpp"
#include "tests/unit/cpu/instructions/status/SEI.cpp"

#include "tests/unit/cpu/instructions/store/STA.cpp"
#include "tests/unit/cpu/instructions/store/STX.cpp"
#include "tests/unit/cpu/instructions/store/STY.cpp"

#include "tests/unit/cpu/instructions/system/BRK.cpp"
#include "tests/unit/cpu/instructions/system/NOP.cpp"
#include "tests/unit/cpu/instructions/system/RTI.cpp"

#include "tests/unit/cpu/instructions/transfer/TAX.cpp"
#include "tests/unit/cpu/instructions/transfer/TAY.cpp"
#include "tests/unit/cpu/instructions/transfer/TXA.cpp"
#include "tests/unit/cpu/instructions/transfer/TYA.cpp"

