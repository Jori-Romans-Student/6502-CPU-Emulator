#include "catch2/catch.hpp"
#include "../../constants.hpp"

TEST_CASE("SBC instruction") {

    // Vars

    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    Word address;
    Byte value;
    Byte A;
    Bit C;

    SECTION("decodes all matching OP codes") {

        Byte OPCodes[8] = { 
            0xE9, 0xE5, 0xF5, 0xED, 0xFD,
            0xF9, 0xE1, 0xF1
        };
        int length = (int) (sizeof(OPCodes) / sizeof(OPCodes[0]));

        for (int i = 0; i < length; i++) {
            REQUIRE(cpu.Instruct(OPCodes[i]) == SBC);
        }
    };

    SECTION("executes properly on zero difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>();
        A = value;
        C = 1;

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == 0x00);
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 1);
    };

    SECTION("executes properly on big-positive to small-positive difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(0, 63);
        A = random<Byte>(65, 127); // ensures a positive value greater then 65
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on small-positive to big-positive difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(65, 126); // ensures a positive value greater then 65
        A = random<Byte>(0, 63); // ensures a positive value less then 64
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on big-negative to small-negative difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(-1, -63); // ensures a negative value less then -64
        A = random<Byte>(-66, -128); // ensures a negative value greater then -65
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on small-negative to big-negative difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(-66, -128); // ensures a negative value greater then -65
        A = random<Byte>(-1, -63); // ensures a negative value less then -64
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on positive to negative difference with positive difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(-1, -63); // ensures a negative value less then -64
        A = random<Byte>(1, 63); // ensures a positive value less then 64
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };

    
    SECTION("executes properly on positive to negative difference with negative difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(-66, -128); // ensures a negative value greater then -65
        A = random<Byte>(66, 126); // ensures a positive value greater then 65
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.V == 1);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on negative to positive difference with negative difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(1, 63); // ensures a positive value less then 64
        A = random<Byte>(-1, -63); // ensures a negative value less then -64
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 1);
        REQUIRE(cpu.V == 0);
        REQUIRE(cpu.N == 1);
        REQUIRE(cpu.Z == 0);
    };

    SECTION("executes properly on negative to positive difference with positive difference") {

        address = random<Word>(0x5000, 0x7FFF);
        value = random<Byte>(66, 126); // ensures a positive value greater then 65
        A = random<Byte>(-66, -128); // ensures a negative value greater then -65
        C = random<Bit>();

        cpu.A = A;
        cpu.C = C;

        mem[address] = value;

        cpu.Execute(SBC, address);

        REQUIRE(cpu.A == (Byte)(A - value - !C));
        REQUIRE(cpu.C == 0);
        REQUIRE(cpu.V == 1);
        REQUIRE(cpu.N == 0);
        REQUIRE(cpu.Z == 0);
    };
}