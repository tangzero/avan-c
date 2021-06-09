#include "instructions.h"
#include <avan/testsuite.h>

CPU *cpu;

void set_up(void)
{
    cpu = cpu_new();
}

void tear_down(void)
{
    cpu_destroy(cpu);
}

void test_adc(void)
{
    cpu->a = 0xF0;
    cpu->flags.carry = true;
    ADC(cpu, 0x0F);
    TEST_ASSERT_EQUAL_HEX8(0x00, cpu->a);
    TEST_ASSERT_TRUE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_add(void)
{
    cpu->a = 0xFF;
    cpu->flags.carry = true;
    ADD(cpu, 0x0F);
    TEST_ASSERT_EQUAL_HEX8(0x0E, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_and(void)
{
    cpu->a = 0b00110101;
    AND(cpu, 0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00100101, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_cp(void)
{
    cpu->a = 0x05;
    CP(cpu, 0xFD);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

int main(void)
{
    SUITE_BEGIN();
    RUN_TEST(test_adc);
    RUN_TEST(test_add);
    RUN_TEST(test_and);
    RUN_TEST(test_cp);
    return SUITE_END();
}
