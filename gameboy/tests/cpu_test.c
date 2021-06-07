#include "greatest.h"

/* A test runs various assertions, then calls PASS(), FAIL(), or SKIP(). */
TEST x_should_equal_1(void)
{
    int x = 1;
    /* Compare, with an automatic "1 != x" failure message */
    ASSERT_EQ(1, x);

    /* Compare, with a custom failure message */
    ASSERT_EQm("Yikes, x doesn't equal 1", 1, x);

    /* Compare, and if they differ, print both values,
   * formatted like `printf("Expected: %d\nGot: %d\n", 1, x);` */
    ASSERT_EQ_FMT(1, x, "%d");
    PASS();
}

/* Suites can group multiple tests with common setup. */
SUITE(the_suite)
{
    RUN_TEST(x_should_equal_1);
}