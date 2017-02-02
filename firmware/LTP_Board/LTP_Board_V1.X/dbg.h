/* 
 * File:   dbg.h
 * Author: paul
 *
 * Created on February 1, 2017, 8:27 PM
 */

#ifndef DBG_H
#define	DBG_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef _DEBUG
#include <stdio.h>
# define dbg_printf(...) printf (__VA_ARGS__)
#else
# define dbg_printf(...)
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* DBG_H */

