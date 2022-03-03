#include "debug.h"
#include <stdlib.h>

#ifdef DEBUG
char *__DEBUG_FILENAME__ = NULL;
FILE *__DEBUG_FILEHANDLE__ = NULL;
short __DEBUG_FILEHANDLE_FAILED__ = 0;
struct timeval __DEBUG_TV__;
char __DEBUG_TM_STR__[DEBUG_TM_STR_LEN];
#endif // DEBUG

