/* [styx_hdl.h]  Test module for dynamic loadable user-defined preprocessing, scan & parse handlers */
/* ------------------------------------------------------------------------- */
/*                                                                           */
/* [styx_hdl.c]      Test modul for dynamic loadable user-defined            */
/*                   preprocessing, scan & parse handlers                    */
/*                                                                           */
/* Copyright (c) 2002 by D\olle, Manns.                                      */
/* ------------------------------------------------------------------------- */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef styx_hdl_INCL
#define styx_hdl_INCL


#include "standard.h"
#include "scn_base.h"
#include "ptm_gen.h"
#include "ptm_pp.h"


#ifdef __cplusplus
extern "C" {
#endif


symbol STYHDL_premac
       (
         Scn_Stream pStream, c_string cTokNam,
         c_string cTokVal, symbol* cMacVal
       )
/* user-defined preprocessing handler */
;

symbol STYHDL_pp(symbol tok, symbol val)
/* user-defined pp token conversion handler */
;

symbol STYHDL_shift(symbol tok, symbol val); /* user-defined shift handler  */
PT_Term STYHDL_reduce(PT_Term tree);   /* user-defined reduce handler       */


#ifdef __cplusplus
}
#endif

#endif
