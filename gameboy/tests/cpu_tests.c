#include "cpu.h"
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

void test_nothing(void)
{
    TEST_ASSERT_NOT_NULL(cpu);
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_nothing);
    return UNITY_END();
}
