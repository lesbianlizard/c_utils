#ifndef CSTR_UTILS_H
#define CSTR_UTILS_H

#define NAME Strs
#define DTYPE char*
#define C_STRING_MODE
#include "dyn_array.h"
#undef NAME
#undef DTYPE
#undef C_STRING_MODE

char *
cstrcat(char *, char *);

int
mmap_file_cstr(char *, int *, char **);

int
strReplace(char *, char *, char *, char **);

int
strTokenSplit(char *, Strs *, char *);

#endif // CSTR_UTILS_H
