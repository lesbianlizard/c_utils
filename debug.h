/* FIXME: how to use:
 - define DEBUG and DEBUG_FILE in your program
 - DEBUG_FILE env var
*/
#ifndef DEBUG_H
#define DEBUG_H

// to be copied and modified by user
#include "debug_config.h"

#ifdef DEBUG

#ifndef DEBUG_SRC_FILES_DELIMITER 
#define DEBUG_SRC_FILES_DELIMITER ','
#endif

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
  char **src_files_arr;
  size_t n_src_files;
#endif // DEBUG_SRC_FILES
#ifdef DEBUG_FUNCTIONS
  char **functions_arr;
  size_t n_functions;
#endif // DEBUG_FUNCTIONS
};

extern struct debuginfo __DEBUG_INFO__;

// FIXME: should DEBUG_CLOSE be called somewhere?
#define DEBUG_CLOSE(...) \
   do {\
      if (__DEBUG_INFO__.filehandle) {fclose(__DEBUG_INFO__.filehandle);}\
   } while (0)

#if defined(DEBUG_SRC_FILES) || defined(DEBUG_FUNCTIONS)
#define _DEBUG_CHECK_ARRAY(ARRAY, ARRAY_SIZE, STR_COMPARE, RESULT) \
if (ARRAY_SIZE > 0 || !ARRAY) \
{ \
  RESULT = 0; \
  \
  for (size_t i = 0; i < ARRAY_SIZE; i++) \
  { \
    if (strcmp(ARRAY[i], STR_COMPARE) == 0) \
    { \
      RESULT = 1; \
      break; \
    } \
  } \
}
#else // defined(DEBUG_SRC_FILES) || defined(DEBUG_FUNCTIONS)
#define _DEBUG_CHECK_ARRAY(...)
#endif // defined(DEBUG_SRC_FILES) || defined(DEBUG_FUNCTIONS)

#ifdef DEBUG_FUNCTIONS
#define _DEBUG_CHECK_FUNCTIONS _DEBUG_CHECK_ARRAY(__DEBUG_INFO__.functions_arr, __DEBUG_INFO__.n_functions, __FUNCTION__, function)
#else // DEBUG_FUNCTIONS
#define _DEBUG_CHECK_FUNCTIONS
#endif // DEBUG_FUNCTIONS

#ifdef DEBUG_SRC_FILES
#define _DEBUG_CHECK_SRC_FILES _DEBUG_CHECK_ARRAY(__DEBUG_INFO__.src_files_arr, __DEBUG_INFO__.n_src_files, __FILE__, src_file)
#else // DEBUG_SRC_FILES
#define _DEBUG_CHECK_SRC_FILES
#endif // DEBUG_SRC_FILES

#define DEBUG_PRINTF(...) \
  do { \
    short src_file = 1, function = 1; \
    \
    _DEBUG_CHECK_FUNCTIONS \
    _DEBUG_CHECK_SRC_FILES \
    \
    if (__DEBUG_INFO__.file_open_failed) \
    { \
      fprintf(stderr, "DEBUG: error in debug.h: cannot open file '%s'\n", __DEBUG_INFO__.filename); \
    } \
    else if (src_file || function)\
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

#ifdef DEBUG_SRC_FILES
void
_DEBUG_PROCESS_ENVVAR(char *, char ***, size_t *);
#endif // DEBUG_SRC_FILES

#else //DEBUG
#define DEBUG_PRINTF(...)
#define DEBUG_INIT(...)
#endif //DEBUG

#endif //DEBUG_H
