#pragma once

#include "cpu.h"

void _adc(CPU *cpu, u8 value);
void _add(CPU *cpu, u8 value);
void _and(CPU *cpu, u8 value);
void _cp(CPU *cpu, u8 value);
u8   _dec(CPU *cpu, u8 value);
u8   _inc(CPU *cpu, u8 value);
void _or(CPU *cpu, u8 value);
void _sbc(CPU *cpu, u8 value);
void _sub(CPU *cpu, u8 value);
void _xor(CPU *cpu, u8 value);
