#include "instructions.h"

void adc(CPU *cpu, u8 value) {
  u8  a = cpu->a;
  u16 sum = a + value + cpu->flags.carry;

  cpu->a = sum & 0x00ff;
  cpu->flags.zero = cpu->a == 0x00;
  cpu->flags.subtration = false;
  cpu->flags.half_carry = ((a & 0x0f) + (value & 0x0f) + cpu->flags.carry) > 0x0f;
  cpu->flags.carry = sum > 0x00ff;
}

void add(CPU *cpu, u8 value) {
  u8  a = cpu->a;
  u16 sum = a + value;

  cpu->a = sum & 0x00ff;
  cpu->flags.zero = cpu->a == 0x00;
  cpu->flags.subtration = false;
  cpu->flags.half_carry = ((a & 0x0f) + (value & 0x0f)) > 0x0f;
  cpu->flags.carry = sum > 0x00ff;
}
