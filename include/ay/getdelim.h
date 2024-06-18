/* SPDX-License-Identifier: 0BSD */

/*
 * To use this single-file library, create a file getdelim.c with the following
 * content: (or just copy src/ay/getdelim.c)
 *
 * #define AY_GETDELIM_IMPLEMENTATION
 * #include "<location of header>"
 */

#ifndef AY_GETDELIM_H
#define AY_GETDELIM_H

#include <stddef.h>
#include <stdlib.h>

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#include <sys/types.h>
#elif defined(_MSC_VER)
#include <basetsd.h>
typedef SSIZE_T ssize_t;
#else
typedef ptrdiff_t ssize_t;
#endif

#ifdef AY_GETDELIM_IMPLEMENTATION

#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
#define _POSIX_C_SOURCE 200809L
#endif /* defined(__unix__) || (defined(__APPLE__) && defined(__MACH__)) */

#include <errno.h>
#include <stdio.h>

#if defined(_POSIX_C_SOURCE)
static void ay__flockfile(FILE *stream) { flockfile(stream); }
static int ay__getc_unlocked(FILE *stream) { return getc_unlocked(stream); }
static void ay__funlockfile(FILE *stream) { funlockfile(stream); }
#elif defined(_MSC_VER)
static void ay__flockfile(FILE *stream) { _lock_file(stream); }
static int ay__getc_unlocked(FILE *stream) { return _getc_nolock(stream); }
static void ay__funlockfile(FILE *stream) { _unlock_file(stream); }
#else
static void ay__flockfile(FILE *stream) {}
static int ay__getc_unlocked(FILE *stream) { return getc(stream); }
static void ay__funlockfile(FILE *stream) {}
#endif

#define INITIAL_BUFFSZ 128

ssize_t getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,
                 FILE *restrict stream) {
  if (lineptr == NULL || stream == NULL || n == NULL) {
    errno = EINVAL;
    return -1;
  }

  ay__flockfile(stream);

  int c = ay__getc_unlocked(stream);
  if (c == EOF)
    return -1;

  if (*lineptr == NULL) {
    *lineptr = malloc(INITIAL_BUFFSZ);
    if (*lineptr == NULL) {
      errno = ENOMEM;
      return -1;
    }
    *n = INITIAL_BUFFSZ;
  }

  size_t pos = 0;
  while (c != EOF) {
    if (pos + 1 >= *n) {
      size_t new_size = *n + (*n >> 2);
      if (new_size < INITIAL_BUFFSZ) {
        new_size = INITIAL_BUFFSZ;
      }
      char *new_ptr = realloc(*lineptr, new_size);
      if (new_ptr == NULL) {
        errno = ENOMEM;
        return -1;
      }
      *n = new_size;
      *lineptr = new_ptr;
    }

    ((unsigned char *)(*lineptr))[pos++] = c;
    if (c == delimiter)
      break;

    c = ay__getc_unlocked(stream);
  }

  (*lineptr)[pos] = '\0';

  if (stream)
    ay__funlockfile(stream);

  return pos;
}

ssize_t getline(char **restrict lineptr, size_t *restrict n,
                FILE *restrict stream) {
  return getdelim(lineptr, n, '\n', stream);
}
#endif /* AY_GETDELIM_IMPLEMENTATION */

#ifndef AY_GETDELIM_IMPLEMENTATION
#include <stdio.h>
#endif /* AY_GETDELIM_IMPLEMENTATION */

ssize_t getdelim(char **restrict lineptr, size_t *restrict n, int delimiter,
                 FILE *restrict stream);

ssize_t getline(char **restrict lineptr, size_t *restrict n,
                FILE *restrict stream);

#endif /* AY_GETDELIM_H */
