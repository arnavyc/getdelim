/**
 * Copyright 2021 arnavyc <arnavyc@outlook.com>
 *
 * SPDX-License-Identifier: 0BSD
 */

#include <ay/getdelim.h>
#include <errno.h>
#include <setjmp.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <munit.h>

#include "tests.h"

int main(int argc, char *argv[]) {
  MunitSuite suites[] = {
      getdelim_test_suite,
      getline_test_suite,
      NULL,
  };

  MunitSuite suite = {
      (char *)"",             /* name */
      NULL,                   /* tests */
      suites,                 /* suites */
      1,                      /* iterations */
      MUNIT_SUITE_OPTION_NONE /* options */
  };

  return munit_suite_main(&suite, NULL, argc, argv);
}
