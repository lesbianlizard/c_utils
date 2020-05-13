#ifndef CSTR_UTILS_H
#define CSTR_UTILS_H

// Concatenate two C strings, dynamically allocating memory for the result
// FIXME: do something different for the count variable
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

#endif // CSTR_UTILS_H
