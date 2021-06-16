#include <stdio.h>
#include "src/hardware/cpu.cpp"

int main() {

    Mem mem;

    mem[0x0042] = 3;

    printf("%d\n", mem[0x0042]);

    return 0;
}
