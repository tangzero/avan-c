#include "instructions.h"

void ADC(CPU *cpu, u8 value)
{
    u8  a = cpu->a;
    u16 sum = a + value + cpu->flags.carry;

    cpu->a = sum & 0x00ff;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = ((a & 0x0f) + (value & 0x0f) + cpu->flags.carry) > 0x0f;
    cpu->flags.carry = sum > 0x00ff;
}

void ADD(CPU *cpu, u8 value)
{
    u8  a = cpu->a;
    u16 sum = a + value;

    cpu->a = sum & 0x00ff;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = ((a & 0x0f) + (value & 0x0f)) > 0x0f;
    cpu->flags.carry = sum > 0x00ff;
}

void AND(CPU *cpu, u8 value)
{
    cpu->a &= value;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = true;
    cpu->flags.carry = false;
}

void CP(CPU *cpu, u8 value)
{
}
