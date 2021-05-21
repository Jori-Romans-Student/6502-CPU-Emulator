#include "src/constants.hpp"
#include <stdio.h>

int main() {
    // Mem mem = Mem();
    // CPU cpu = CPU(&mem);

    // for (int i = 0; i < 0xFF; i++) {
    //     mem[0x0100] = (Byte) 0xA0;
    //     mem[0x5795] = (Byte) 0x00;
    //     cpu.PC = 0x0100;
    //     cpu.A = (Byte) i;

    //     cpu.Run();

    //     printf("A is %X; Mem is %X\n", cpu.A, mem[0x5795]);
    // }

    // for (int i = 0; i < 0xff; i++) {
    //     Byte value = cpu.Decode((Byte) i);
    //     printf("Received value of %X for OP Code %X\n", value, (Byte) i);
    // }

    Bit C = 1;
    Bit Z = 0;
    Bit I = 1;
    Bit D = 0;
    Bit B = 0;
    Bit V = 1;
    Bit N = 0;

    // Processor Byte

    Status P = Status(&C, &Z, &I, &D, &B, &V, &N);

    Byte hello = (Byte) P;

    return 0;
}
