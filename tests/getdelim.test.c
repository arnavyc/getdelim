/**
 * Copyright 2021 arnavyc <arnavyc@outlook.com>
 *
 * SPDX-License-Identifier: 0BSD
 */

#include <ay/getdelim.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include <munit.h>

#include "tests.h"

static MunitResult test_getdelim(const MunitParameter params[],
                                 void *user_data_or_fixture) {
  FILE *fp = tmpfile();
  munit_assert_not_null(fp);

  const char *line_written = "This  is a test";
  int rc = fprintf(fp, "%s", line_written);
  munit_assert_int(strlen(line_written), ==, rc);

  rewind(fp);

  char *word_read = NULL;
  size_t allocated_length = 0;

  const char *expected[] = {"This ", " ", "is ", "a ", "test"};
  for (size_t i = 0; i < 5; ++i) {
    munit_assert_false(feof(fp));
    munit_assert_int(getdelim(&word_read, &allocated_length, ' ', fp), ==,
                     strlen(expected[i]));
    munit_assert_int(allocated_length, >=, strlen(expected[i]));
    munit_assert_string_equal(word_read, expected[i]);
  }

  // Last read should've set EOF indicator for the stream
  munit_assert_true(feof(fp));
  clearerr(fp);

  // getdelim return -1 but doesn't set errno if we're already at EOF
  // It should set EOF indicator for the stream, though
  errno = 0;
  munit_assert_int(getdelim(&word_read, &allocated_length, ' ', fp), ==, -1);
  munit_assert_int(errno, ==, 0);
  munit_assert_true(feof(fp));

  free(word_read);
  fclose(fp);

  return MUNIT_OK;
}

static MunitTest tests[] = {
    {
        (char *)"/getdelim",    /* name */
        test_getdelim,          /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite getdelim_test_suite = {
    (char *)"/getdelim",    /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};
