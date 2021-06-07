#include "instructions.h"

#include "greatest.h"

TEST test_adc(void) {
  CPU *cpu = new_gameboy_cpu();
  cpu->a = 0xf0;
  cpu->flags.carry = true;

  adc(cpu, 0x0f);

  ASSERT_EQ_FMT(0x00, cpu->a, "0x%02x");
  ASSERT(cpu->flags.zero);
  ASSERT_FALSE(cpu->flags.subtration);
  ASSERT(cpu->flags.half_carry);
  ASSERT(cpu->flags.carry);
  PASS();
}

TEST test_add(void) {
  CPU *cpu = new_gameboy_cpu();
  cpu->a = 0xff;
  cpu->flags.carry = true;

  add(cpu, 0x0f);

  ASSERT_EQ_FMT(0x0e, cpu->a, "0x%02x");
  ASSERT_FALSE(cpu->flags.zero);
  ASSERT_FALSE(cpu->flags.subtration);
  ASSERT(cpu->flags.half_carry);
  ASSERT(cpu->flags.carry);
  PASS();
}

SUITE(instructions_suite) {
  RUN_TEST(test_adc);
  RUN_TEST(test_add);
}
