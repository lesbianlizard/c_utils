#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG
#define DEBUG_FILE "debug.log"

// // yes this weirdness is needed
// // TODO: find out why
// #define _CONCAT(x,y) x ## y
// #define CONCAT(x,y) _CONCAT(x,y)

#ifdef DEBUG

#include <stdio.h>
#include <stdlib.h> //getenv
#include <time.h>
#include <sys/time.h>

#ifdef DEBUG_FILE
// could use inline and avoid the need for a separate compilation unit but
// that needs -std=c++17
extern char* __DEBUG_FILENAME__;
extern FILE* __DEBUG_FILEHANDLE__;
extern struct timeval __DEBUG_TV__;
extern struct timeval __DEBUG_PREV_TV__;
#define DEBUG_TM_STR_LEN 10
extern char __DEBUG_TM_STR__[DEBUG_TM_STR_LEN];

#define DEBUG_CLOSE(...) \
   do {\
      if (__DEBUG_FILEHANDLE__) {fclose(__DEBUG_FILEHANDLE__);}\
   } while (0)

#else //DEBUG_FILE
#define DEBUG_FILEHANDLE stderr
#define DEBUG_CLOSE(...)
#endif //DEBUG_FILE

#define DEBUG_PRINTF(...) \
   do { \
   if (!__DEBUG_FILEHANDLE__) { \
      __DEBUG_FILENAME__ = getenv("DEBUG_FILE") ? getenv("DEBUG_FILE") : DEBUG_FILE; \
      __DEBUG_FILEHANDLE__ = fopen(__DEBUG_FILENAME__, "w");\
   } \
   gettimeofday(&__DEBUG_TV__, NULL); \
   strftime(__DEBUG_TM_STR__,DEBUG_TM_STR_LEN,"%H:%M:%S",localtime(&__DEBUG_TV__.tv_sec)); \
   fprintf(__DEBUG_FILEHANDLE__, "DEBUG [%s.%.3li] [%s+%i/%s]: ",__DEBUG_TM_STR__,__DEBUG_TV__.tv_usec/1000,__FILE__,__LINE__,__FUNCTION__); \
   fprintf(__DEBUG_FILEHANDLE__, __VA_ARGS__);\
   fprintf(__DEBUG_FILEHANDLE__, "\n");\
   fflush(__DEBUG_FILEHANDLE__);\
   } while (0)


#else //DEBUG
#define DEBUG_PRINTF(...)
#endif //DEBUG

#endif //DEBUG_H
