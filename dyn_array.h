// This file implements a simple dynamic array system for an arbitrary data type DTYPE
// You must #define the following values before including this file:
//   NAME: this is the name of the array type, used as the struct name and in all function names
//   DTYPE: the array will be of this data type
//   C_STRING_MODE: if defined, run free() on every element of the array before free()ing the
//     DYPE *d object. Use strcmp rather than explicit comparision for some functions.
#define CONCAT(a, b) CONCAT_(a, b)
#define CONCAT_(a, b) a ## b

typedef struct {
  DTYPE *d;
  size_t allocated;
  size_t used;
} NAME;

// Initialize a NAME object
void CONCAT(init, NAME)(NAME* new_arr)
{
  const size_t initSize = 2;
  new_arr->d = malloc(initSize * sizeof(DTYPE));
  new_arr->allocated = initSize;
  new_arr->used = 0;
}

// Free all memory allocated in a NAME
void CONCAT(dealloc, NAME)(NAME* arr)
{
  #ifdef C_STRING_MODE
  size_t i;

  for (i = 0; i < arr->used; i++)
  {
    free(arr->d[i]);
  }
  #endif

  free(arr->d);
}

// Double size of allocated memory
void CONCAT(_grow, NAME)(NAME* arr)
{
  arr->d = realloc(arr->d, arr->allocated*2*sizeof(DTYPE));
  arr->allocated *= 2;
}

// Add a new element to the end of a NAME array
void CONCAT(push, NAME)(NAME* arr, DTYPE new_element)
{
  if (!(arr->used < arr->allocated))
  {
    CONCAT(_grow, NAME)(arr);
  }

  arr->d[arr->used] = new_element;
  arr->used++;
}

// Find the first occurence of search in arr and return its index.
// Return SIZE_MAX if search is not in arr.
size_t CONCAT(contains, NAME)(NAME* arr, DTYPE search)
{
  size_t i;

  for (i = 0; i < arr->used; i++)
  {
    #ifdef C_STRING_MODE
    if (strcmp(search, arr->d[i]) == 0)
    {
      return i;
    }
    #else
    if (search == arr->d[i])
    {
      return i;
    }
    #endif
  }
  
  return SIZE_MAX;
}

// Remove all elements of a NAME array at an index greater than or equal to idx
void CONCAT(truncate, NAME)(NAME* arr, size_t idx)
{
  #ifdef C_STRING_MODE
  size_t i;

  for (i = idx; i < arr->used; i++)
  {
    free(arr->d[i]);
    arr->d[i] = NULL;
  }
  #endif

  arr->used = idx;
}

// Remove one element from a NAME array, shifting over other elements to fill its place
void CONCAT(removeIdx, NAME)(NAME* arr, size_t idx)
{
  size_t i;

  for (i = idx; i < arr->used - 1; i++)
  {
    arr->d[i] = arr->d[i + 1];
  }

  CONCAT(truncate, NAME)(arr, arr->used - 1);
}

// Remove all elements in a NAME array with elements equal to element, shifting over
// other elements to fill their places.
void CONCAT(removeVals, NAME)(NAME* arr, DTYPE element)
{
  size_t i = CONCAT(contains, NAME)(arr, element);

  while (i < SIZE_MAX)
  {
    i = CONCAT(contains, NAME)(arr, element);

    if (i < SIZE_MAX)
    {
      CONCAT(removeIdx, NAME)(arr, i);
    }
  }
}
