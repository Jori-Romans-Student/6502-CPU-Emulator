#include "catch2/catch.hpp"
#include "../constants.hpp"

TEST_CASE("Decode Method of CPU") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    SECTION("for Absolute addressing codes") {

        Byte OPCodes[23] = { 
            0xAD, 0xAE, 0xAC, 0x6D, 0x2D,
            0x0E, 0x2C, 0xCD, 0xEC, 0xCC,
            0xCE, 0x4D, 0xEE, 0x4C, 0x20,
            0x4E, 0x0D, 0x2E, 0x6E, 0xED,
            0x8D, 0x8E, 0x8C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == AB);
        }
    };

    SECTION("for Absolute X addressing codes") {

        Byte OPCodes[15] = { 
            0xBD, 0xBC, 0x7D, 0x3D, 0x1E,
            0xDD, 0xDE, 0x5D, 0xFE, 0x5E,
            0x1D, 0x3E, 0x7E, 0xFD, 0x9D
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ABX);
        }
    };

    SECTION("for Absolute Y addressing codes") {

        Byte OPCodes[9] = { 
            0xB9, 0xBE, 0x79, 0x39, 0xD9,
            0x59, 0x19, 0xF9, 0x99
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ABY);
        }
    };

    SECTION("for Accumulator addressing codes") {

        Byte OPCodes[29] = { 
            0x00, 0x18, 0xD8, 0x58, 0xB8, 
            0x48, 0x08, 0x68, 0x28, 0x40,
            0x60, 0x38, 0xF8, 0x78, 0xAA,
            0xA8, 0xBA, 0x8A, 0x9A, 0x98,
            0x0A, 0x2A, 0x4A, 0x6A, 0xCA,
            0x88, 0xE8, 0xC8, 0xEA
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == AC);
        }
    };

    SECTION("for Immediate addressing codes") {

        Byte OPCodes[11] = { 
            0xA9, 0xA2, 0xA0, 0x69, 0x29,
            0xC9, 0xE0, 0xC0, 0x49, 0x09,
            0xE9
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IMM);
        }
    };

    SECTION("for Indirect addressing codes") {

        Byte OPCodes[1] = { 
            0x6C
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ID);
        }
    };

    SECTION("for Indirect X addressing codes") {

        Byte OPCodes[8] = { 
            0xA1, 0x61, 0x21, 0xC1, 0x41,
            0x01, 0xE1, 0x81
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IDX);
        }
    };

    SECTION("for Indirect Y addressing codes") {

        Byte OPCodes[8] = { 
            0xB1, 0x71, 0x31, 0xD1, 0x51,
            0x11, 0xF1, 0x91
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == IDY);
        }
    };

    SECTION("for Relative addressing codes") {

        Byte OPCodes[8] = { 
            0x10, 0x30, 0x50, 0x70, 0x90,
            0xB0, 0xD0, 0xF0
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == REL);
        }
    };

    SECTION("for Zero Page addressing codes") {

        Byte OPCodes[21] = { 
            0xA5, 0xA6, 0xA4, 0x65, 0x25,
            0x06, 0x24, 0xC5, 0xE4, 0xC4,
            0xC6, 0x45, 0xE6, 0x46, 0x05,
            0x26, 0x66, 0xE5, 0x85, 0x86, 
            0x84
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ZP);
        }
    };

    SECTION("for Zero Page X addressing codes") {

        Byte OPCodes[16] = { 
            0xB5, 0xB4, 0x75, 0x35, 0x16,
            0xD5, 0xD6, 0x55, 0xF6, 0x56,
            0x15, 0x36, 0x76, 0xF5, 0x95,
            0x94
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ZPX);
        }
    };

    SECTION("for Zero Page Y addressing codes") {

        Byte OPCodes[2] = { 
            0xB6, 0x96
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Decode(OPCodes[i]) == ZPY);
        }
    };
}