#pragma once

#include <base/types.h>
#include <stdbool.h>

typedef struct CPU {
    u8 a;           // accumulator
    u16 bc, de, hl; // generic registers
    u16 sp;         // stack pointer
    u16 pc;         // program counter
    struct {
        bool zero;        // Z
        bool subtraction; // N
        bool half_carry;  // H
        bool carry;       // C
    } flags;
} CPU;

CPU *cpu_new();
void cpu_destroy(CPU *cpu);
