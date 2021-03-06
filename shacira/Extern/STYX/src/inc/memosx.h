/* -------------------------------------------------------------------------- */
/*                                                                            */
/* [memosx.h(mem_base)]        Memory Management                              */
/*                                                                            */
/* Copyright (c) 1993 by D\olle, Manns                                        */
/* -------------------------------------------------------------------------- */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef mem_base_INCL
#define mem_base_INCL


#include "sysbase0.h"


#ifdef __cplusplus
extern "C" {
#endif


/* ------------------------------- Memory ----------------------------------- */

long ObjCount(void);                   /* allocated objects                 */

StdCPtr NewMem(long objsize)
/* creates an object of size 'objsize'; raises exception */
;


#if !defined(HAVE_CONFIG_H) || defined(HAVE_REALLOC)

StdCPtr ResizeMem(StdCPtr Any, long objsize)
/* resizes an object to size 'objsize'; raises exception */
;


#endif

void FreeMem(StdCPtr Any);             /* frees object 'Any'                */


#ifdef __cplusplus
}
#endif

#endif
