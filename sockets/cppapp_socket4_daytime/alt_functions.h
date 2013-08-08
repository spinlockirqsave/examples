/* 
 * File:   alt_functions.h
 * Author: root
 *
 * Created on July 24, 2013, 1:41 AM
 */

#ifndef ALT_FUNCTIONS_H
#define	ALT_FUNCTIONS_H

#ifdef	__cplusplus
extern "C" {
#endif

/* alt_functions.h

   Header file for alt_functions.c.
*/


#if defined(__osf__) || defined(__hpux) || defined(_AIX) || \
        defined(__sgi) || defined(__APPLE__)
#define strsignal(sig) ALT_strsignal(sig)
#endif
char *ALT_strsignal(int sig);

#if defined(__hpux) || defined(__osf__)
#define hstrerror(err) ALT_hstrerror(err)
#endif
char *ALT_hstrerror(int sig);

#if defined(__hpux) || defined(__osf__)
#define posix_openpt(flags) ALT_posix_openpt(flags)
#endif
int ALT_posix_openpt(int flags);



#ifdef	__cplusplus
}
#endif

#endif	/* ALT_FUNCTIONS_H */

