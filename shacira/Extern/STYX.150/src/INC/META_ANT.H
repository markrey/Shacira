/* ------------------------------------------------------------------------ */
/*                                                                          */
/* [meta_ant.h]               Language Interface                            */
/*                                                                          */
/* ------------------------------------------------------------------------ */

/* File generated by 'ctoh'. Don't change manually. */

#ifndef meta_ant_INCL
#define meta_ant_INCL


#include "ptm.h"
#include "gls_abs.h"


#ifdef __cplusplus
extern "C" {
#endif


/* --------------------- symbol objects - init & quit --------------------- */

void meta_initSymbols();               /*                                   */
void meta_quitSymbols();               /*                                   */

/* -------------------------- Types & Constants --------------------------- */

AbstractHugeType( meta );

AbstractHugeType( metaSource );
AbstractHugeType( metaTyp  );
AbstractHugeType( metaElm  );

/* --------------------------- Access to Tokens --------------------------- */

c_bool Tmeta_Ide(GLS_Tok x);           /*                                   */

/* --------------------------- Access to Terms ---------------------------- */

c_bool meta_meta(PT_Abs_Term x, meta* x1);         /*                       */
c_bool meta_Source(PT_Abs_Term x, metaSource* x1); /*                       */
c_bool meta_Typ(PT_Abs_Term x, metaTyp* x1);       /*                       */
c_bool meta_Elm(PT_Abs_Term x, metaElm* x1);       /*                       */

/* --------------------------------- meta --------------------------------- */

c_bool meta_Start_Source(meta x, metaSource* x1)
#define meta_Start_0   meta_Start_Source
;


/* -------------------------------- Source -------------------------------- */

c_bool metaSource_dfn(metaSource x, GLS_Lst(metaElm)* x1); /*               */

/* --------------------------------- Typ ---------------------------------- */

c_bool metaTyp_dfn(metaTyp x, GLS_Tok* x1); /*                              */
c_bool metaTyp_nul(metaTyp x);              /*                              */

/* --------------------------------- Elm ---------------------------------- */

c_bool metaElm_grp(metaElm x, GLS_Tok* x1, metaTyp* x2,
                   GLS_Lst(metaElm)* x3)
;

c_bool metaElm_txt(metaElm x);         /*                                   */


#ifdef __cplusplus
}
#endif

#endif
