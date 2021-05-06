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
    Range<Byte> Y;
};

void run(void (*script)(Mem&, CPU&), CPUConfig config) {

    // Initialize Memory and CPU

    Mem mem;
    CPU cpu;

    // Run from PC Start to PC end

    for (int PC = config.PC.start; PC <= config.PC.end; PC++) {

        // Run from X start to X end

        for (int X = config.X.start; X <= config.X.end; X++) {

            // Run from Y start to Y end

            for (int Y = config.Y.start; Y <= config.Y.end; Y++) {
                // Reset memory on every run and reinitialize PC

                cpu.Reset( mem );
                cpu.PC = (Word) PC;
                cpu.X = (Byte) X;
                cpu.Y = (Byte) Y;
                
                // Run script

                script(mem, cpu);
            }
        }
    }
}