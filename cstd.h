#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdint.h>
#include <limits.h>
#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>


typedef double f64_t;
typedef float f32_t;


/* Runtime panic with printf formatted error message */
#define m_error(FMT, ...) { \
  printf("Internal error at [%s:%d]: ", __FILE__, __LINE__); \
  printf(FMT, ## __VA_ARGS__); \
  putchar('\n'); \
  abort(); \
}

/* Runtime assertion with panic and printf formatted error message if the boolean condition is not true */
#define m_assert(COND, FMT, ...) if (!(COND)) m_error(FMT, ## __VA_ARGS__)


/* Get the index offset of a pointer from the base address of it's buffer */
inline size_t pointer_to_index (void const* base, void const* instance, size_t size) {
  return ((uintptr_t) base - (uintptr_t) instance) / size;
}