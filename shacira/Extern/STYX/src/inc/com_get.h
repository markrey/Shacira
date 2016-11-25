/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [com_get.h]            Comment Line Extraction                           */
/*                                                                          */
/* Copyright (c) 1993 by D\olle, Manns                                      */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef com_get_INCL
#define com_get_INCL


#include "standard.h"


#ifdef __cplusplus
extern "C" {
#endif


c_string Com_GetEx(c_string FileName)
/* [basename]#title of source 'FileName'
   format: ['FileName'] ...
         | ['FileName'(basename)] ...
   ( doesn't allocs memory )
*/
;

c_string Com_Get(c_string FileName)
/* title of source 'FileName'
   format: ['FileName'] ...
   ( doesn't allocs memory )
*/
;



#ifdef __cplusplus
}
#endif

#endif