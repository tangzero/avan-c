#include "instructions.h"
#include <unity.h>

#define set_up setUp
#define set_down tearDown

CPU *cpu;

void set_up(void)
{
    cpu = new_gameboy_cpu();
}

void set_down(void)
{
    destroy_gameboy_cpu(cpu);
}

void test_adc(void)
{
    cpu->a = 0xf0;
    cpu->flags.carry = true;

    ADC(cpu, 0x0f);

    TEST_ASSERT_EQUAL_HEX8(0x00, cpu->a);
    TEST_ASSERT_TRUE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_add(void)
{
    cpu->a = 0xff;
    cpu->flags.carry = true;

    ADD(cpu, 0x0f);

    TEST_ASSERT_EQUAL_HEX8(0x0e, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_adc);
    RUN_TEST(test_add);
    return UNITY_END();
}
