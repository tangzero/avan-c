#include "greatest.h"

GREATEST_MAIN_DEFS();

extern greatest_suite_cb the_suite;

int main(int argc, char **argv)
{
  GREATEST_MAIN_BEGIN();
  RUN_SUITE(the_suite);
  GREATEST_MAIN_END();
}