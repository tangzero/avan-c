#include <base/testsuite.h>
#include "instructions.h"

CPU *cpu;

void set_up(void) { cpu = cpu_new(); }

void tear_down(void) { cpu_destroy(cpu); }

void test_adc(void) {
    cpu->a = 0xF0;
    cpu->flags.carry = true;
    ADC(cpu, 0x0F);
    TEST_ASSERT_EQUAL_HEX8(0x00, cpu->a);
    TEST_ASSERT_TRUE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_add(void) {
    cpu->a = 0xFF;
    cpu->flags.carry = true;
    ADD(cpu, 0x0F);
    TEST_ASSERT_EQUAL_HEX8(0x0E, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_and(void) {
    cpu->a = 0b00110101;
    AND(cpu, 0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00100101, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_cp(void) {
    cpu->a = 0x05;
    CP(cpu, 0xFD);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_dec(void) {
    u8 result = DEC(cpu, 0x1F);
    TEST_ASSERT_EQUAL_HEX8(0x1E, result);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_inc(void) {
    u8 result = INC(cpu, 0xB0);
    TEST_ASSERT_EQUAL_HEX8(0xB1, result);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_or(void) {
    cpu->a = 0b00110101;
    OR(cpu, 0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00111101, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_sbc(void) {
    cpu->a = 0x1A;
    cpu->flags.carry = true;
    SBC(cpu, 0x1F);
    TEST_ASSERT_EQUAL_HEX8(0xFA, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_sub(void) {
    cpu->a = 0xCC;
    SUB(cpu, 0xDC);
    TEST_ASSERT_EQUAL_HEX8(0xF0, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_xor(void) {
    cpu->a = 0b00110101;
    XOR(cpu, 0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00011000, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

int main(void) {
    SUITE_BEGIN();
    RUN_TEST(test_adc);
    RUN_TEST(test_add);
    RUN_TEST(test_and);
    RUN_TEST(test_cp);
    RUN_TEST(test_dec);
    RUN_TEST(test_inc);
    RUN_TEST(test_or);
    RUN_TEST(test_sbc);
    RUN_TEST(test_sub);
    RUN_TEST(test_xor);
    return SUITE_END();
}
