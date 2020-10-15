# c_utils

A collection of pure C functions/utilities I've wanted to share between different projects. Currently most of this stuff originated in the Operating Systems II class while I was developing smallsh.


# Files
## dyn_array.h

This is a really simple dynamic array system. You just `#define` a couple of variables to depending on what datatype you want an array of, then `#include dyn_array.h`. You can include it as many different times as you want with different data types. See the comments in the file for more details.

To use this library, make sure it is in your include path. Then, include the header one or more times, adjusting `NAME`, `DTYPE`, and `C_STRING_MODE` to your needs, like this:
```
#define NAME Strs
#define DTYPE char*
#define C_STRING_MODE
#include "dyn_array.h"
#undef NAME
#undef DTYPE
#undef C_STRING_MODE
```
For the implementations, create a file called for example `dyn_array_proxy.c`, and include the implementation file one or more times as above, replacing `dyn_array.h` with `dyn_array.c`.

## cstr_utils.h
### cstrcat
Concatenates two C strings, dynamically allocating memory for the result.
### mmap_file_cstr
Memory-maps a file for convenient, and efficient, access to large or small files.
### strReplace
Does a simple find-and-replace of two C strings in a 3rd C string, allocating a 4th C string for the result.
### strTokenSplit
Splits a string at a given set of tokens, putting them into an array of C strings from `dyn_array.h`. I made this because I wanted `strtok`-like functionality without the black magic.
