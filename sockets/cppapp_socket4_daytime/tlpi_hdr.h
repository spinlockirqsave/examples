/* 
 * File:   tlpi_hdr.h
 * Author: root
 *
 * Created on July 24, 2013, 1:37 AM
 */

#ifndef TLPI_HDR_H
#define	TLPI_HDR_H

#ifdef	__cplusplus
extern "C" {
#endif

/* tlpi_hdr.h

   Standard header file used by nearly all of our example programs.
*/

#include <sys/types.h>  /* Type definitions used by many programs */
#include <stdio.h>      /* Standard I/O functions */
#include <stdlib.h>     /* Prototypes of commonly used library functions,
                           plus EXIT_SUCCESS and EXIT_FAILURE constants */
#include <unistd.h>     /* Prototypes for many system calls */
#include <errno.h>      /* Declares errno and defines error constants */
#include <string.h>     /* Commonly used string-handling functions */

#include "get_num.h"    /* Declares our functions for handling numeric
                           arguments (getInt(), getLong()) */

#include "error_functions.h"  /* Declares our error-handling functions */

/* Unfortunately some UNIX implementations define FALSE and TRUE -
   here we'll undefine them */

#ifdef TRUE
#undef TRUE
#endif

#ifdef FALSE
#undef FALSE
#endif

typedef enum { FALSE, TRUE } Boolean;

#define min(m,n) ((m) < (n) ? (m) : (n))
#define max(m,n) ((m) > (n) ? (m) : (n))

/* Some systems don't define 'socklen_t' */

#if defined(__sgi)
typedef int socklen_t;
#endif

/* The remainder of this file creates various definitions to help
   the example programs run on UNIX implementations other than Linux. */

#include "alt_functions.h"      /* Declares simple replacements for some
                                   functions that are absent on other systems */

#if defined(__sun)
#include <sys/file.h>           /* Has definition of FASYNC */
#endif

#if ! defined(O_ASYNC) && defined(FASYNC)
/* Some systems define FASYNC instead of O_ASYNC */
#define O_ASYNC FASYNC
#endif

#if defined(MAP_ANON) && ! defined(MAP_ANONYMOUS)
/* BSD derivatives usually have MAP_ANON, not MAP_ANONYMOUS */
#define MAP_ANONYMOUS MAP_ANON

#endif

#if ! defined(O_SYNC) && defined(O_FSYNC)
/* Some implementations have O_FSYNC instead of O_SYNC */
#define O_SYNC O_FSYNC
#endif

#if defined(__FreeBSD__)

/* FreeBSD uses these alternate names for fields in the sigval structure */

#define sival_int sigval_int
#define sival_ptr sigval_ptr
#endif


#ifdef	__cplusplus
}
#endif

#endif	/* TLPI_HDR_H */

