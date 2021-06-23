/*
 * Copyright 2021 arnavyc <arnavyc@outlook.com>
 * SPDX-License-Identifier: 0BSD
 *
 * Licensed under the Zero Clause BSD License. See LICENSE.md file in the
 * project root, or https://opensource.org/licenses/0BSD for full license
 * information.
 */

#include <stdio.h>
#include <stdlib.h>

#include <ay/getdelim.h>

int main(int argc, char *argv[]) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread = getline(&line, &len, stdin);

  printf("Retrived line of length: %zd.\n", nread);

  free(line);
  return EXIT_SUCCESS;
}
