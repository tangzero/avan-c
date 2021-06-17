#include "instructions.h"
#include <base/testsuite.h>

CPU *cpu;

void set_up() {
    cpu = cpu_new();
}

void tear_down() {
    cpu_destroy(cpu);
}

void test_adc() {
    A = 0xF0;
    CARRY = true;
    ADC(0x0F);
    TEST_ASSERT_EQUAL_HEX8(0x00, cpu->a);
    TEST_ASSERT_TRUE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_add8() {
    A = 0xFF;
    CARRY = true;
    ADD8(0x0F);
    TEST_ASSERT_EQUAL_HEX8(0x0E, A);
    TEST_ASSERT_FALSE(ZERO);
    TEST_ASSERT_FALSE(SUBTRACTION);
    TEST_ASSERT_TRUE(HALF_CARRY);
    TEST_ASSERT_TRUE(CARRY);
}

void test_and() {
    cpu->a = 0b00110101;
    AND(0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00100101, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_cp() {
    A = 0x05;
    CP(0xFD);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_dec8() {
    A = 0x1F;
    DEC8(A);
    TEST_ASSERT_EQUAL_HEX8(0x1E, A);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_inc8() {
    A = 0xB0;
    INC8(A);
    TEST_ASSERT_EQUAL_HEX8(0xB1, result);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_or() {
    A = 0b00110101;
    OR(0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00111101, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_sbc() {
    A = 0x1A;
    cpu->flags.carry = true;
    SBC(0x1F);
    TEST_ASSERT_EQUAL_HEX8(0xFA, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_sub() {
    cpu->a = 0xCC;
    SUB(0xDC);
    TEST_ASSERT_EQUAL_HEX8(0xF0, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_TRUE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_TRUE(cpu->flags.carry);
}

void test_xor() {
    cpu->a = 0b00110101;
    XOR(0b00101101);
    TEST_ASSERT_EQUAL_HEX8(0b00011000, cpu->a);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_add16() {
    cpu->hl = 0x0FFF;
    cpu->flags.carry = true;
    ADD16(0x0001);
    TEST_ASSERT_EQUAL_HEX16(0x1000, cpu->hl);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_dec16() {
    BC = 0x0F0F;
    DEC16(BC);
    TEST_ASSERT_EQUAL_HEX16(0x0F0E, BC);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_inc16() {
    DE = 0xABCD;
    INC16(DE);
    TEST_ASSERT_EQUAL_HEX16(0xABCE, DE);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_bit() {
    A = 0b00010101;
    BIT(5, A);
    TEST_ASSERT_TRUE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_TRUE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_res() {
    A = 0b11111111;
    RES(5, A);
    TEST_ASSERT_EQUAL_HEX8(0b11011111, A);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_set() {
    A = 0b00000000;
    SET(2, A);
    TEST_ASSERT_EQUAL_HEX8(0b00000100, A);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

void test_swap() {
    A = 0xAB;
    SWAP(A);
    TEST_ASSERT_EQUAL_HEX8(0xBA, A);
    TEST_ASSERT_FALSE(cpu->flags.zero);
    TEST_ASSERT_FALSE(cpu->flags.subtraction);
    TEST_ASSERT_FALSE(cpu->flags.half_carry);
    TEST_ASSERT_FALSE(cpu->flags.carry);
}

int main() {
    SUITE_BEGIN();
    RUN_TEST(test_adc);
    RUN_TEST(test_add8);
    RUN_TEST(test_and);
    RUN_TEST(test_cp);
    RUN_TEST(test_dec8);
    RUN_TEST(test_inc8);
    RUN_TEST(test_or);
    RUN_TEST(test_sbc);
    RUN_TEST(test_sub);
    RUN_TEST(test_xor);
    RUN_TEST(test_add16);
    RUN_TEST(test_dec16);
    RUN_TEST(test_inc16);
    RUN_TEST(test_bit);
    RUN_TEST(test_res);
    RUN_TEST(test_set);
    RUN_TEST(test_swap);
    return SUITE_END();
}
