#ifndef DEBUG_CONFIG_H
#define DEBUG_CONFIG_H

#define DEBUG
//#define DEBUG_FILE "debug.log"
#define DEBUG_SRC_FILES
#define DEBUG_FUNCTIONS

#define DEBUG_LEVELS
#define DEBUG_LEVEL_ENUM_DEF  LOOP, TRACE, INFO, WARNING, ERROR
#define DEBUG_LEVEL_ENUM_STR  {"loop", "trace", "info", "warning", "error"}
// number of elements above
#define DEBUG_LEVEL_ENUM_SIZE 5
// ensure this is long enough for the strings in DEBUG_LEVEL_ENUM_STR
#define DEBUG_LEVEL_ENUM_STRLEN (7 + 1)

#define DEBUG_LEVEL_DEFAULT TRACE
#define DEBUG_MIN_LEVEL_DEFAULT INFO

#define DEBUG_LEVEL_ALWAYSSHOW_ENABLE
#define DEBUG_LEVEL_MIN_ALWAYSSHOW ERROR

#endif // DEBUG_CONFIG_H
