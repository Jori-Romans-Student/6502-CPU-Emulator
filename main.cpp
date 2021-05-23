#include "src/constants.hpp"
#include <stdio.h>

int main() {
    // Mem mem = Mem();
    // CPU cpu = CPU(&mem);

    //Byte hello = random<Byte>(127, 127);
    Byte hello = random<Byte>();
    Byte neg = negative<Byte>(hello);

    printf("%d\n", hello);
    printf("%d\n", neg);

    return 0;
}
