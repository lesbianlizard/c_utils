#include "debug.h"

#ifdef DEBUG
#include <stdlib.h>
#include <string.h>

struct debuginfo __DEBUG_INFO__;

int
_DEBUG_INIT(void)
{
#ifdef DEBUG_FILE
  __DEBUG_INFO__.filehandle = fopen(DEBUG_FILE, "w");
  __DEBUG_INFO__.file_open_failed = __DEBUG_INFO__.filehandle ? 0 : 1;
#else // DEBUG_FILE
  __DEBUG_INFO__.filename = getenv("DEBUG_FILE");

  /* if environment var is set AND isn't empty*/
  if (__DEBUG_INFO__.filename && (strlen(__DEBUG_INFO__.filename) > 0))
  {
    __DEBUG_INFO__.filehandle = fopen(__DEBUG_INFO__.filename, "w");
    __DEBUG_INFO__.file_open_failed = __DEBUG_INFO__.filehandle ? 0 : 1;
  }
  else
  {
    __DEBUG_INFO__.filehandle = stderr;
  }
#endif // DEBUG_FILE

#ifdef DEBUG_SRC_FILES
_DEBUG_PROCESS_ENVVAR("DEBUG_SRC_FILES", &__DEBUG_INFO__.src_files_arr, &__DEBUG_INFO__.n_src_files);
#endif // DEBUG_SRC_FILES

#ifdef DEBUG_FUNCTIONS
_DEBUG_PROCESS_ENVVAR("DEBUG_FUNCTIONS", &__DEBUG_INFO__.functions_arr, &__DEBUG_INFO__.n_functions);
#endif // DEBUG_SRC_FILES

return 0;
}

#if defined(DEBUG_SRC_FILES) || defined(DEBUG_FUNCTIONS)
void
_DEBUG_PROCESS_ENVVAR(char *envvar_str, char ***arr, size_t *arr_size)
{
  char *string = getenv(envvar_str);

  if (string)
  {
    if (string && (strlen(string) > 0))
    {
      char *tmp1 = string - 1;

      // count number of files specified in environment variable
      while (tmp1)
      {
        tmp1++;
        tmp1 = strchr(tmp1, DEBUG_SRC_FILES_DELIMITER);
        (*arr_size)++;
      }

      *arr = calloc(*arr_size, sizeof(char *));

      // store each filename into an array
      for (size_t i = 0; i < *arr_size; i++)
      {
        size_t len;
        tmp1 = strchr(string, DEBUG_SRC_FILES_DELIMITER);

        if (tmp1)
        {
          len = tmp1 - string;
        }
        else
        {
          len = strlen(string);
        }

        (*arr)[i] = calloc(len + 1, sizeof(char));
        strncpy((*arr)[i], string, len);
        string = tmp1 + 1;
      }
    }
  }
  else
  {
    *arr = (void *) 1;
  }

}
#endif // defined(DEBUG_SRC_FILES) || defined(DEBUG_FUNCTIONS)

#endif // DEBUG
