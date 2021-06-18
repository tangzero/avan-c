#pragma once

#include "cpu.h"

#define ZERO        cpu->flags.zero
#define SUBTRACTION cpu->flags.subtraction
#define HALF_CARRY  cpu->flags.half_carry
#define CARRY       cpu->flags.carry

#define A      cpu->a
#define BC     cpu->bc
#define DE     cpu->de
#define HL     cpu->hl
#define SP     cpu->sp
#define B      ((BC >> 8) & 0x00FF)
#define C      (BC & 0x00FF)
#define D      ((DE >> 8) & 0x00FF)
#define E      (DE & 0x00FF)
#define H      ((HL >> 8) & 0x00FF)
#define L      (HL & 0x00FF)
#define MEMORY cpu_read(cpu, HL)
#define BYTE   cpu_read_next_byte(cpu)

#define SET_A(x)      (A = (x))
#define SET_BC(x)     (BC = (x))
#define SET_DE(x)     (DE = (x))
#define SET_HL(x)     (HL = (x))
#define SET_SP(x)     (SP = (x))
#define SET_B(x)      (BC |= ((x) << 8) & 0xFF00)
#define SET_C(x)      (BC |= (x)&0x00FF)
#define SET_D(x)      (DE |= ((x) << 8) & 0xFF00)
#define SET_E(x)      (DE |= (x)&0x00FF)
#define SET_H(x)      (HL |= ((x) << 8) & 0xFF00)
#define SET_L(x)      (HL |= (x)&0x00FF)
#define SET_MEMORY(x) cpu_write(cpu, HL, x)

#define ADC(value)                                                                                                     \
    u8 a = A;                                                                                                          \
    u16 sum = a + value + CARRY;                                                                                       \
    A = sum & 0x00FF;                                                                                                  \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = ((a & 0x0F) + (value & 0x0F) + CARRY) > 0x0F;                                                         \
    CARRY = sum > 0x00FF;

#define ADD8(value)                                                                                                    \
    u8 a = A;                                                                                                          \
    u16 sum = a + value;                                                                                               \
    A = sum & 0x00FF;                                                                                                  \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = ((a & 0x0F) + (value & 0x0F)) > 0x0F;                                                                 \
    CARRY = sum > 0x00FF;

#define AND(value)                                                                                                     \
    A &= value;                                                                                                        \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = true;                                                                                                 \
    CARRY = false;

#define CP(value)                                                                                                      \
    u16 result = A - value;                                                                                            \
    ZERO = result == 0x00;                                                                                             \
    SUBTRACTION = true;                                                                                                \
    HALF_CARRY = (result & 0x0F) > (A & 0x0F);                                                                         \
    CARRY = result < 0x00;

#define DEC8(value)                                                                                                    \
    u8 result = value - 1;                                                                                             \
    ZERO = result == 0x00;                                                                                             \
    SUBTRACTION = true;                                                                                                \
    HALF_CARRY = (value & 0x0F) == 0x0F;                                                                               \
    SET_##value(result);

#define INC8(value)                                                                                                    \
    u8 result = value + 1;                                                                                             \
    ZERO = result == 0x00;                                                                                             \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = (value & 0x0F) == 0x00;                                                                               \
    SET_##value(result);

#define OR(value)                                                                                                      \
    A |= value;                                                                                                        \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = false;                                                                                                \
    CARRY = false;

#define SBC(value)                                                                                                     \
    u8 a = A;                                                                                                          \
    A -= value + CARRY;                                                                                                \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = true;                                                                                                \
    HALF_CARRY = ((value & 0x0F) + CARRY) > (a & 0x0F);                                                                \
    CARRY = (value + CARRY) > a;

#define SUB(value)                                                                                                     \
    u8 a = A;                                                                                                          \
    A -= value;                                                                                                        \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = true;                                                                                                \
    HALF_CARRY = (value & 0x0F) > (a & 0x0F);                                                                          \
    CARRY = value > a;

#define XOR(value)                                                                                                     \
    A ^= value;                                                                                                        \
    ZERO = A == 0x00;                                                                                                  \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = false;                                                                                                \
    CARRY = false;

#define ADD16(value)                                                                                                   \
    u16 hl = HL;                                                                                                       \
    u32 sum = hl + value;                                                                                              \
    HL = sum & 0x0000FFFF;                                                                                             \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = ((hl & 0x0FFF) + (value & 0x0FFF)) > 0x0FFF;                                                          \
    CARRY = sum > 0x0000FFFF;

#define DEC16(value) SET_##value(--value);

#define INC16(value) SET_##value(++value);

#define BIT(bit, value)                                                                                                \
    ZERO = (value & (1 << bit)) == 0x00;                                                                               \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = true;

#define RES(bit, value) SET_##value(value ^ (1 << bit));

#define SET(bit, value) SET_##value(value | (1 << bit));

#define SWAP(value)                                                                                                    \
    SET_##value((value >> 4) | (value << 4));                                                                          \
    ZERO = value == 0x00;                                                                                              \
    SUBTRACTION = false;                                                                                               \
    HALF_CARRY = false;                                                                                                \
    CARRY = false;
