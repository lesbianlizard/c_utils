#ifndef CSTR_UTILS_H
#define CSTR_UTILS_H

char *
cstrcat(char* str1, char* str2, size_t count)
{
  size_t newsize = 1;
  char* result;

  if (count == SIZE_MAX)
  {
    newsize += strlen(str1) + strlen(str2);
  }
  else
  {
    newsize += strlen(str1) + count;
  }

  result = malloc(newsize * sizeof(char));
  strcat(result, str1);

  if (count == SIZE_MAX)
  {
    strcat(result, str2);
  }
  else
  {
    strncat(result, str2, count);
  }

  return result;
}

#endif // CSTR_UTILS_H
