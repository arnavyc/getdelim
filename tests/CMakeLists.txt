# SPDX-FileCopyrightText: 2021 arnavyc
#
# SPDX-License-Identifier: 0BSD

include(DownloadAndUseMunit)
include(Munit)

add_executable(getdelim_tests main.c getdelim.test.c getline.test.c)
target_link_libraries(getdelim_tests getdelim munit)

munit_discover_tests(getdelim_tests
#  ITERATIONS 5
#  NO_FORK
#  SHOW_STDERR
#  FATAL_FAILURES
#  SINGLE
#  SEED 0xc5
#  PARAMS a b
#  LOG_VISIBLE info
#  LOG_FATAL error
#  EXTRA_ARGS --color always
#  TEST_PREFIX ay_
#  TEST_SUFFIX _ya
)

