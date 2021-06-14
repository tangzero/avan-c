#pragma once

#include "cpu.h"

void ADC(CPU *cpu, u8 value);
void ADD(CPU *cpu, u8 value);
void AND(CPU *cpu, u8 value);
void CP(CPU *cpu, u8 value);
u8   DEC(CPU *cpu, u8 value);
u8   INC(CPU *cpu, u8 value);
void OR(CPU *cpu, u8 value);
void SBC(CPU *cpu, u8 value);
void SUB(CPU *cpu, u8 value);
void XOR(CPU *cpu, u8 value);
