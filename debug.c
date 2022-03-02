#include "debug.h"
#include <stdlib.h>

#ifdef DEBUG
#ifdef DEBUG_FILE
char* __DEBUG_FILENAME__ = NULL;
FILE* __DEBUG_FILEHANDLE__ = NULL;
struct timeval __DEBUG_TV__;
char __DEBUG_TM_STR__[DEBUG_TM_STR_LEN];
#else
FILE* __DEBUG_FILEHANDLE__ = DEBUG_FILEHANDLE;
#endif
#endif

