// This file implements a simple dynamic array system for an arbitrary data type DTYPE
// You must #define the following values before including this file:
//   NAME: this is the name of the array type, used as the struct name and in all function names
//   DTYPE: the array will be of this data type
//   C_STRING_MODE: if defined, run free() on every element of the array before free()ing the
//     DYPE *d object. Use strcmp rather than explicit comparision for some functions.
//#ifndef DYN_ARRAY_H
//#define DYN_ARRAY_H

#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

//#ifndef CONCAT(DYN_ARRAY_H_, NAME)
//#define CONCAT(DYN_ARRAY_H_, NAME)
#include <stddef.h>

typedef struct {
  DTYPE *d;
  size_t allocated;
  size_t used;
} NAME;

void
CONCAT(init, NAME)(NAME* new_arr);

void
CONCAT(dealloc, NAME)(NAME* arr);

void
CONCAT(_grow, NAME)(NAME* arr);

void
CONCAT(push, NAME)(NAME* arr, DTYPE new_element);

size_t
CONCAT(contains, NAME)(NAME* arr, DTYPE search);

void
CONCAT(truncate, NAME)(NAME* arr, size_t idx);

void
CONCAT(removeIdx, NAME)(NAME* arr, size_t idx);

void
CONCAT(removeVals, NAME)(NAME* arr, DTYPE element);

//#endif // DYN_ARRAY_H
//#endif // CONCAT(DYN_ARRAY_H_, NAME)
