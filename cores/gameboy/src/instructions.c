#include "instructions.h"

#define UNUSED(x) (void)(x)

void _adc(CPU *cpu, u8 value) {
    u8  a = cpu->a;
    u16 sum = a + value + cpu->flags.carry;

    cpu->a = sum & 0x00FF;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = ((a & 0x0F) + (value & 0x0F) + cpu->flags.carry) > 0x0F;
    cpu->flags.carry = sum > 0x00FF;
}

void _add8(CPU *cpu, u8 value) {
    u8  a = cpu->a;
    u16 sum = a + value;

    cpu->a = sum & 0x00FF;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = ((a & 0x0F) + (value & 0x0F)) > 0x0F;
    cpu->flags.carry = sum > 0x00FF;
}

void _and(CPU *cpu, u8 value) {
    cpu->a &= value;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = true;
    cpu->flags.carry = false;
}

void _cp(CPU *cpu, u8 value) {
    u16 result = cpu->a - value;
    cpu->flags.zero = result == 0x00;
    cpu->flags.subtraction = true;
    cpu->flags.half_carry = (result & 0x0F) > (cpu->a & 0x0F);
    cpu->flags.carry = result < 0x00;
}

u8 _dec8(CPU *cpu, u8 value) {
    u8 result = value - 1;
    cpu->flags.zero = result == 0x00;
    cpu->flags.subtraction = true;
    cpu->flags.half_carry = (value & 0x0F) == 0x0F;
    return result;
}

u8 _inc8(CPU *cpu, u8 value) {
    u8 result = value + 1;
    cpu->flags.zero = result == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = (value & 0x0F) == 0x00;
    return result;
}

void _or(CPU *cpu, u8 value) {
    cpu->a |= value;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = false;
    cpu->flags.carry = false;
}

void _sbc(CPU *cpu, u8 value) {
    u8 a = cpu->a;
    cpu->a -= value + cpu->flags.carry;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = true;
    cpu->flags.half_carry = ((value & 0x0F) + cpu->flags.carry) > (a & 0x0F);
    cpu->flags.carry = (value + cpu->flags.carry) > a;
}

void _sub(CPU *cpu, u8 value) {
    u8 a = cpu->a;
    cpu->a -= value;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = true;
    cpu->flags.half_carry = (value & 0x0F) > (a & 0x0F);
    cpu->flags.carry = value > a;
}

void _xor(CPU *cpu, u8 value) {
    cpu->a ^= value;
    cpu->flags.zero = cpu->a == 0x00;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = false;
    cpu->flags.carry = false;
}

void _add16(CPU *cpu, u16 value) {
    u16 hl = cpu->hl;
    u32 sum = hl + value;

    cpu->hl = sum & 0x0000FFFF;
    cpu->flags.subtraction = false;
    cpu->flags.half_carry = ((hl & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF;
    cpu->flags.carry = sum > 0x0000FFFF;
}

u16 _dec16(CPU *cpu, u16 value) {
    UNUSED(cpu);
    return --value;
}

u16 _inc16(CPU *cpu, u16 value) {
    UNUSED(cpu);
    return ++value;
}
