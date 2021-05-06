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

    // Range for X and Y Register

    Range<Byte> X;
};

void run(void (*script)(Mem&, CPU&), CPUConfig config) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Run from PC Start to PC end

    for (int PC = config.PC.start; PC <= config.PC.end; PC++) {

        for (int X = config.X.start; X <= config.X.end; X++) {
            
            // Reset memory on every run and reinitialize PC

            cpu.Reset( mem );
            cpu.PC = (Word) PC;
            cpu.X = (Byte) X;
            
            // Run script

            script(mem, cpu);
        }
    }
}