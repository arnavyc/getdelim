/**
 * SPDX-FileCopyrightText: 2021 arnavyc
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

static MunitResult test_getline(const MunitParameter params[],
                                void *user_data_or_fixture) {
  FILE *fp = tmpfile();
  munit_assert_not_null(fp);

  const char *line_written = "We are testing getline()\n";
  const size_t line_count = 10;

  for (size_t i = 0; i < line_count; ++i) {
    int rc = fprintf(fp, "%s", line_written);
    munit_assert_int(strlen(line_written), ==, rc);
  }

  rewind(fp);

  char *line_read = NULL;
  size_t allocated_length = 0;

  size_t read_line_count = 0;
  ssize_t read_char_count;

  while ((read_char_count = getline(&line_read, &allocated_length, fp)) != -1) {
    munit_assert_int(strlen(line_written), ==, read_char_count);
    munit_assert_int(allocated_length, >=, strlen(line_written));
    munit_assert_string_equal(line_read, line_written);
    ++read_line_count;
  }
  munit_assert_int(read_line_count, ==, line_count);

  // Last read should've set EOF indicator for the stream
  munit_assert_true(feof(fp));
  clearerr(fp);

  // getline returns -1 but doesn't set errno if we're already at EOF
  // It should set EOF indicator for the stream, though
  errno = 0;
  munit_assert_int(getline(&line_read, &allocated_length, fp), ==, -1);
  munit_assert_int(errno, ==, 0);
  munit_assert_true(feof(fp));

  free(line_read);
  fclose(fp);

  return MUNIT_OK;
}

static MunitTest tests[] = {
    {
        (char *)"/getline",     /* name */
        test_getline,           /* test */
        NULL,                   /* setup */
        NULL,                   /* tear_down */
        MUNIT_TEST_OPTION_NONE, /* options */
        NULL                    /* parameters */
    },
    /* Mark the end of the array with an entry where the test
     * function is NULL */
    {NULL, NULL, NULL, NULL, MUNIT_TEST_OPTION_NONE, NULL}};

MunitSuite getline_test_suite = {
    (char *)"/getline",     /* name */
    tests,                  /* tests */
    NULL,                   /* suites */
    1,                      /* iterations */
    MUNIT_SUITE_OPTION_NONE /* options */
};
