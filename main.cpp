#include "src/cpu.cpp"
#include <stdio.h>

int main() {
    Mem mem = Mem();
    CPU cpu = CPU(&mem);

    for (int i = 0; i < 0xFF; i++) {
        mem[0x0100] = (Byte) 0xA0;
        mem[0x5795] = (Byte) 0x00;
        cpu.PC = 0x0100;
        cpu.A = (Byte) i;

        cpu.Run();

        printf("A is %X; Mem is %X\n", cpu.A, mem[0x5795]);
    }

    // for (int i = 0; i < 0xff; i++) {
    //     Byte value = cpu.Decode((Byte) i);
    //     printf("Received value of %X for OP Code %X\n", value, (Byte) i);
    // }
    return 0;
}
