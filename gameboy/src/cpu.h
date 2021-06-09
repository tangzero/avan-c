#pragma once

#include "types.h"
#include <stdbool.h>

#define get_b(cpu) ((cpu->bc >> 8) & 0x00ff)
#define set_b(cpu, value) cpu->bc |= (value << 8) & 0xff00
#define get_c(cpu) (cpu->bc & 0x00ff)
#define set_c(cpu, value) cpu->bc |= value & 0x00ff
#define get_d(cpu) ((cpu->de >> 8) & 0x00ff)
#define set_d(cpu, value) cpu->de |= (value << 8) & 0xff00
#define get_e(cpu) (cpu->de & 0x00ff)
#define set_e(cpu, value) cpu->de |= value & 0x00ff
#define get_h(cpu) ((cpu->hl >> 8) & 0x00ff)
#define set_h(cpu, value) cpu->hl |= (value << 8) & 0xff00
#define get_l(cpu) (cpu->hl & 0x00ff)
#define set_l(cpu, value) cpu->hl |= value & 0x00ff

typedef struct CPU
{
    u8  a;          // accumulator
    u16 bc, de, hl; // generic registers
    u16 sp;         // stack pointer
    u16 pc;         // program counter
    struct
    {
        bool zero;        // Z
        bool subtraction; // N
        bool half_carry;  // H
        bool carry;       // C
    } flags;
} CPU;

CPU *new_gameboy_cpu();
void destroy_gameboy_cpu(CPU *cpu);
