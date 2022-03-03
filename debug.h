/* FIXME: how to use:
 - define DEBUG and DEBUG_FILE in your program
 - DEBUG_FILE env var
*/
#ifndef DEBUG_H
#define DEBUG_H

// to be copied and modified by user
#include "debug_config.h"

#ifdef DEBUG

#include <stdio.h>
#include <stdlib.h> //getenv
#include <time.h>
#include <sys/time.h>

#define DEBUG_TM_STR_LEN 10

struct debuginfo
{
  char *filename;
  FILE *filehandle;
  short file_open_failed; // 1 = failed, 0 = not failed
  struct timeval tv;
  char time_str[DEBUG_TM_STR_LEN];
#ifdef DEBUG_SRC_FILES
  char *src_files;
  char **src_files_arr;
  size_t n_src_files;
#endif // DEBUG_SRC_FILES
};

extern struct debuginfo __DEBUG_INFO__;

// FIXME: should DEBUG_CLOSE be called somewhere?
#define DEBUG_CLOSE(...) \
   do {\
      if (__DEBUG_INFO__.filehandle) {fclose(__DEBUG_INFO__.filehandle);}\
   } while (0)


#define DEBUG_PRINTF(...) \
  do { \
    \
    if (__DEBUG_INFO__.file_open_failed) \
    { \
      fprintf(stderr, "DEBUG: error in debug.h: cannot open file '%s'\n", __DEBUG_INFO__.filename); \
    } \
    else \
    { \
      gettimeofday(&__DEBUG_INFO__.tv, NULL); \
      strftime(__DEBUG_INFO__.time_str,DEBUG_TM_STR_LEN,"%H:%M:%S",localtime(&__DEBUG_INFO__.tv.tv_sec)); \
      fprintf(__DEBUG_INFO__.filehandle, "DEBUG [%s.%.3li] [%s+%i/%s]: ",__DEBUG_INFO__.time_str,__DEBUG_INFO__.tv.tv_usec/1000,__FILE__,__LINE__,__FUNCTION__); \
      fprintf(__DEBUG_INFO__.filehandle, __VA_ARGS__);\
      fprintf(__DEBUG_INFO__.filehandle, "\n");\
      fflush(__DEBUG_INFO__.filehandle);\
    } \
  } while (0)


int
_DEBUG_INIT(void);

#define DEBUG_INIT(...) _DEBUG_INIT()

#else //DEBUG
#define DEBUG_PRINTF(...)
#define DEBUG_INIT(...)
#endif //DEBUG



#endif //DEBUG_H
