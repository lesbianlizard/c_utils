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
}

#endif // DEBUG
