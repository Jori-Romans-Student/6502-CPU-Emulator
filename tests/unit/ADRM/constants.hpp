# pragma once

#include "../constants.hpp"
#include <time.h>

template <typename T>
struct Range {
    
    // Start and end of range

    T start;
    T end;
};

struct CPUConfig {
    
    // Range for Program Counter

    Range<Word> PC;
};

void run(void (*script)(Mem&, CPU&), CPUConfig config) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Run from PC Start to PC end

    for (Word PC = config.PC.start; PC < config.PC.end; PC++) {

        // Reset memory on every run and reinitialize PC

        cpu.Reset( mem );
        cpu.PC = PC;
        
        // Run script

        script(mem, cpu);
    }
}