//Debug Macros

// Prevent from including file twice
#ifndef _dbg_h_
#define _dbg_h_

// Includes for functions Macros need
#include <stdio.h>
#include <errno.h>
#include <string.h>

// If compiled with NDEBUG defined then "no debug" messages will be shown.
#ifndef NDEBUG
#define debug(M, ...)
#else
//Translates use of debug("format", arg1, arg2) into an fprintf
// ##_VA_ARGS_ says "put whatever the extra arguments here"
// _FILE_ and _LINE_ get current file:line of debug message
#define debug(M, ...) fprintf(stderr,"DEBUG %s:%d: "M"\n",_FILE_, _LINE_, ##_VA_ARGS_);
#endif

//Used by the other Macros to get a safe readable version of errno
#define clean_errno()(errno == 0 ? "None":strerror(errno))

//log_err, log_warn, log_info for logging messages meant for end user.
//Works like debug but cannot be compiled out.
#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__,__LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__,__LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

// Will check if condition A is true. If not logs the error M then jumps to the functions error for cleanup
#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

// Placed in any part of a function that shouldn't run
// Used to catch conditions that shouldn't happen
#define sentinel(M, ...) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

//Checks if a pointer is valid. Reports error "out of memory" if not valid
#define check_mem(A) check((A), "Out of memory.")

// If the error is common then don't bother reporting it
#define check_debug(A, M, ...) if(!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
