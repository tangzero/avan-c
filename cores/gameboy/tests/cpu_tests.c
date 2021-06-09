#include <base/testsuite.h>
#include "cpu.h"

CPU *cpu;

void set_up(void) { cpu = cpu_new(); }

void tear_down(void) { cpu_destroy(cpu); }

void test_nothing(void) { TEST_ASSERT_NOT_NULL(cpu); }

int main(void) {
  SUITE_BEGIN();
  RUN_TEST(test_nothing);
  return SUITE_END();
}
