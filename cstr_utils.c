#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>

#define NAME Strs
#define DTYPE char*
#define C_STRING_MODE
#include "dyn_array.h"
#undef NAME
#undef DTYPE
#undef C_STRING_MODE

#ifndef _
#define _(asdf) (asdf)
#endif


// Concatenate two C strings, dynamically allocating memory for the result
char *
cstrcat(char* str1, char* str2)
{
  size_t newsize = 1;
  char* result;

  newsize += strlen(str1) + strlen(str2);
  result = malloc(newsize * sizeof(char));
  result[newsize - 1] = 0;

  strcat(result, str1);
  strcat(result, str2);

  return result;
}

// Memory map a file to a C string. Don't forget to close(fd_ret) when you're done with it!
int
mmap_file_cstr(char *name, int *fd_ret, char **cstr_ret)
{
  int fd = open(name, O_RDONLY);

  if (fd > 0)
  {
    int len = lseek(fd, 0, SEEK_END);
    *cstr_ret = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
    *fd_ret = fd;
    return 0;
  }
  else
  {
    fprintf(stderr, _("[%1$s] error %2$i opening file '%3$s': %4$s\n"),
      __func__,
      errno,
      name,
      strerror(errno));
    return -1;
  }
}

// This function replaces all instances of find with replace in string,
// storing the result in a newly-allocated buffer *dest.
int
strReplace(char* string, char* find, char* replace, char** dest)
{
  char *where,
       *result = NULL,
       *string_orig = string,
       *where2;
  size_t len = 0,
         len_from_orig,
         find_len = strlen(find),
         replace_len = strlen(replace),
         string_len = strlen(string),
         len_prev = 0;
  int found = 0;

  // Set where to the first occurance of find in string, if it exists
  where = strstr(string, find);

  while (! (where == NULL))
  {
    found = 1;
    // How far along the string is find?
    len_from_orig = where - string;
    len_prev = len;
    len += len_from_orig + replace_len;
    result = realloc(result, (len + 1) * sizeof(char));
    memset(result + len_prev, 0, len - len_prev);
    // copy plain part of string
    strncat(result, string, len_from_orig);
    // copy replacement
    strncat(result, replace, replace_len);
    // Offset string so that we don't find the same 'find' again
    string = where + find_len;

    if (string > (string_orig + string_len))
    {
      where = NULL;
    }
    else
    {
      where2 = where;
      where = strstr(string, find);

      // In this case, there is something at the end of the string we need to copy
      if (where == NULL)
      {
        len_prev = len;
        len += strlen(where2);
        result = realloc(result, (len + 1) * sizeof(char));
        memset(result + len_prev, 0, len - len_prev);
        strcat(result, string);
      }
    }
  }

  // Either return original string, or a new one
  if (found == 0)
  {
    dest[0] = string;
    return 1;
  }
  else
  {
    dest[0] = result;
    return 0;
  }
}

// Splits line at token characters, putting them into the Strs* arr data structure
// FIXME: unused variable, define return values
int
strTokenSplit(char* line_in, Strs* arr, char* token)
{
  char *line = line_in,
       *temp2;
  size_t arglen;

  // If the user entered nothing, do not attempt to parse
  if (strlen(line) == 0)
  {
    return -1;
  }

  while(! ((line == NULL)))
  {
    // Ignore tokens
    while (strpbrk(line, token) == line)
    {
      line++;

      // If we got to the end of the string alreay, just return
      if ((line + 1) > line + strlen(line))
      {
        return 0;
      }
    }

    if (strpbrk(line, token) == NULL)
    {
      // There are no more tokens, so we want the entire remaining string
      arglen = strlen(line);
    }
    else
    {
      // Read up until the next occurance of a token
      arglen = strpbrk(line, token) - line;
    }

    // Read arglen characters into a new string
    temp2 = malloc((arglen + 1) * sizeof(char));
    memset(temp2, 0, (arglen + 1) * sizeof(char));
    strncpy(temp2, line, arglen);
    pushStrs(arr, temp2);
    // Skip to next token
    line = strpbrk(line, token);
  }

  return 0;
}

