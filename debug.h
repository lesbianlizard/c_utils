/* FIXME: how to use:
 - define DEBUG and DEBUG_FILE in your program
 - DEBUG_FILE env var
*/
#ifndef DEBUG_H
#define DEBUG_H

// FIXME: these should be defined by the user
#define DEBUG
//#define DEBUG_FILE "debug.log"

#ifdef DEBUG

#include <stdio.h>
#include <stdlib.h> //getenv
#include <time.h>
#include <sys/time.h>

// could use inline and avoid the need for a separate compilation unit but
// that needs -std=c++17
extern char *__DEBUG_FILENAME__;
extern FILE *__DEBUG_FILEHANDLE__;
extern short __DEBUG_FILEHANDLE_FAILED__; // 1 = failed, 0 = not failed
extern struct timeval __DEBUG_TV__;
extern struct timeval __DEBUG_PREV_TV__;
#define DEBUG_TM_STR_LEN 10
extern char __DEBUG_TM_STR__[DEBUG_TM_STR_LEN];

// FIXME: should DEBUG_CLOSE be called somewhere?
#define DEBUG_CLOSE(...) \
   do {\
      if (__DEBUG_FILEHANDLE__) {fclose(__DEBUG_FILEHANDLE__);}\
   } while (0)


#ifdef DEBUG_FILE
#define __DEBUG_PRINTF_SETUP_FILEHANDLE(...) \
{ \
  __DEBUG_FILEHANDLE__ = fopen(DEBUG_FILE, "w"); \
  __DEBUG_FILEHANDLE_FAILED__ = __DEBUG_FILEHANDLE__ ? 0 : 1; \
}
#else // DEBUG_FILE
#define __DEBUG_PRINTF_SETUP_FILEHANDLE(...) \
{ \
  __DEBUG_FILENAME__ = getenv("DEBUG_FILE"); \
  /* if environment var is set AND isn't empty*/ \
  if (__DEBUG_FILENAME__ && (strlen(__DEBUG_FILENAME__) > 0)) \
  { \
    __DEBUG_FILEHANDLE__ = fopen(__DEBUG_FILENAME__, "w"); \
    __DEBUG_FILEHANDLE_FAILED__ = __DEBUG_FILEHANDLE__ ? 0 : 1; \
  } \
  else \
  { \
    __DEBUG_FILEHANDLE__ = stderr; \
  } \
}
#endif // DEBUG_FILE


#define DEBUG_PRINTF(...) \
  do { \
    if (!__DEBUG_FILEHANDLE__ && !__DEBUG_FILEHANDLE_FAILED__) \
    { \
      __DEBUG_PRINTF_SETUP_FILEHANDLE(); \
    } \
    \
    if (__DEBUG_FILEHANDLE_FAILED__) \
    { \
      fprintf(stderr, "DEBUG: error in debug.h: cannot open file '%s'\n", __DEBUG_FILENAME__); \
    } \
    else \
    { \
      gettimeofday(&__DEBUG_TV__, NULL); \
      strftime(__DEBUG_TM_STR__,DEBUG_TM_STR_LEN,"%H:%M:%S",localtime(&__DEBUG_TV__.tv_sec)); \
      fprintf(__DEBUG_FILEHANDLE__, "DEBUG [%s.%.3li] [%s+%i/%s]: ",__DEBUG_TM_STR__,__DEBUG_TV__.tv_usec/1000,__FILE__,__LINE__,__FUNCTION__); \
      fprintf(__DEBUG_FILEHANDLE__, __VA_ARGS__);\
      fprintf(__DEBUG_FILEHANDLE__, "\n");\
      fflush(__DEBUG_FILEHANDLE__);\
    } \
  } while (0)


#else //DEBUG
#define DEBUG_PRINTF(...)
#endif //DEBUG

#endif //DEBUG_H
